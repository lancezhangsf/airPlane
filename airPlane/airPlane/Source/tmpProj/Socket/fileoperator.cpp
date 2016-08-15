/*
 * fileoperator.cpp
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#include "fileoperator.h"
#include <sys/sendfile.h>
#include <memory.h>

const int MAX_BUFFERLENGTH = 512 * 1024;

FileOperator::FileOperator() :
		filePtr(NULL) {
}

FileOperator::~FileOperator() {
	Close();
}

bool FileOperator::Open(const char* fileName, const char* option) {
	filePtr = fopen(fileName, option);
	return filePtr != NULL;
}

int FileOperator::WriteToFile(const std::string& buffer) {
	int writeBytes = ::fwrite(buffer.c_str(), sizeof(char), buffer.size(),
			filePtr);

	if (writeBytes < 0) {
		perror("error from fwrite");
		return -1;
	} else if (writeBytes == 0)
		return 0;
	else
		return writeBytes;
}

int FileOperator::ReadFromFile(std::string& buffer) {
	char bufferArray[MAX_BUFFERLENGTH + 1];
	buffer.clear();
	memset(bufferArray, 0, MAX_BUFFERLENGTH + 1);

	int numberRead = fread(bufferArray, sizeof(char), MAX_BUFFERLENGTH + 1,
			filePtr);
	if (numberRead == -1) {
		perror("error in Socket::Receive");
		return -1;
	} else if (numberRead == 0)
		return 0;
	else {
		buffer = bufferArray;
		return numberRead;
	}
}

int FileOperator::ReadFromFileBinary(std::string &buffer) {

	return 1;
}

void FileOperator::Close() {
	if (filePtr != NULL)
		fclose(filePtr);
}

