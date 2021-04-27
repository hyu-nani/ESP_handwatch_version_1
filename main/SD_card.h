


File dataFile;

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    
    Serial.printf("SD : Listing directory: %s\n", dirname);
    File root = fs.open(dirname);
    if(!root){
        Serial.println("SD : Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("SD : Not a directory");
        return;
    }

    File file = root.openNextFile();
    int k=0;
    while(file){
        if(file.isDirectory()){
            //Serial.print("  DIR : ");
            //Serial.println(file.name());
            //listDirName[k]=file.name();
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            //Serial.print("  FILE: ");
            //Serial.print(file.name());
            //listDirName[k]=file.name();
            Serial.print("SD :  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
void createDir(fs::FS &fs, const char * path){
    Serial.printf("SD : Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("SD : Dir created");
    } else {
        Serial.println("SD : mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("SD : Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("SD : Dir removed");
    } else {
        Serial.println("SD : rmdir failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("SD : Reading file: %s\n", path);
    File file = fs.open(path);
    if(!file){
        Serial.println("SD : Failed to open file for reading");
        return;
    }

    Serial.print("SD : Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}
void loadImage(fs::FS &fs, unsigned short array[] ,const char * path){
	SD_CS_Clr();
	Serial.printf("SD : loading image file: %s\n", path);
	File file = fs.open(path);
	if(!file){
		Serial.println("SD : Failed to open file for reading");
		return;
	}
	int k=0;
	word A,B,C,D;
	char code;
	word color_data;
	while(file.available())
	{
		//Serial.write(file.read());
		//Serial.write('\n');
		code = char(file.read());
		if(code == '0')
		{
			if(char(file.read()) == 'x')
			{
				A = convert_CtoB(char(file.read())) << 12;
				B = convert_CtoB(char(file.read())) << 8;
				C = convert_CtoB(char(file.read())) << 4;
				D = convert_CtoB(char(file.read()));
				array[k] = A+B+C+D;
				k++;
			}
		}
		else if(code == '/'||code == '[') //주석 제거 remove //
		{
			for(int j=0;j<5;j++)
				file.read();
		}
	}
	file.close();
	Serial.println("SD : done!");
	SD_CS_Set();
}
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("SD : Writing file: %s\n", path);
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("SD : Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("SD : File written");
    } else {
        Serial.println("SD : Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("SD : Appending to file: %s\n", path);
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("SD : Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("SD : Message appended");
    } else {
        Serial.println("SD : Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("SD : Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("SD : File renamed");
    } else {
        Serial.println("SD : Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("SD : Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("SD : File deleted");
    } else {
        Serial.println("SD : Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("SD : %u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("SD : Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("SD : Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("SD : %u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}


uint8_t cardType;
uint64_t cardSize; //total size
uint64_t cardUse; //use data size

void SD_init()
{
	SD_CS_Clr(); //active sd
	if(!SD.begin(SD_CS)){
		Serial.println("SD : Card Mount Failed");
		connect_SD == false;
		return;
	}
	connect_SD = true;
	cardType = SD.cardType();
	
	if(cardType == CARD_NONE){
		Serial.println("SD : No SD card attached");
		return;
	}
	Serial.print("SD : SD Card Type: ");
	if(cardType == CARD_MMC){
		Serial.println("SD : MMC");
	} else if(cardType == CARD_SD){
		Serial.println("SD : SDSC");
	} else if(cardType == CARD_SDHC){
		Serial.println("SD : SDHC");
	} else {
		Serial.println("SD : UNKNOWN");
	}

	cardSize = SD.cardSize() / (1024 * 1024);
	Serial.printf("SD : SD Card Size: %lluMB\n", cardSize);

	listDir(SD, "/", 0);
	//createDir(SD, "/mydir");
	//listDir(SD, "/", 0);
	//removeDir(SD, "/mydir");
	//listDir(SD, "/", 2);
	//writeFile(SD, "/hello.txt", "Hello ");
	//appendFile(SD, "/hello.txt", "World!\n");
	//readFile(SD, "/hello.txt");
	//deleteFile(SD, "/foo.txt");
	//renameFile(SD, "/hello.txt", "/foo.txt");
	//readFile(SD, "/foo.txt");
	//testFileIO(SD, "/test.txt");
	cardUse =  SD.usedBytes() / (1024 * 1024);
	Serial.printf("SD : Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
	Serial.printf("SD : Used space: %lluMB\n",cardUse);
	
	loadImage(SD,load_image, "SD : /Background_image/health_background.c");
	
	SD_CS_Set();
}


void read_data_file(){
	SD_CS_Clr(); //active sd
  /*
	const char * path = "/wifi_password.txt";
	Serial.printf("Reading file: %s\n", path);
	File file = fs.open(path);
	if(!file){
		Serial.println("Failed to open file for reading");
		return;
	}
	Serial.print("Read from file: ");
	char filedata[500];
	int i = 0;
	while(file.available()){
		filedata[i] = file.read();
		Serial.write(filedata[i]);
		i++;
	}
	file.close();
	*/
	
	SD_CS_Set();
}
