/*
 * fileoperator.h
 *
 *  Created on: 2016年5月26日
 *      Author: root
 */

#ifndef SOCKET_FILEOPERATOR_H_
#define SOCKET_FILEOPERATOR_H_


#include <stdio.h>

#define WRITE_CREATE_MODE "a+b"

#include <fcntl.h>
#include <string>

class FileOperator
{
    public:
        FileOperator();
        ~FileOperator();
        bool Open(const char* fileName,const char* option);
        int WriteToFile(const std::string& buffer);
        int ReadFromFile(std::string& buffer);
        int ReadFromFileBinary(std::string &buffer);
        void Close();

    private:
        FILE* filePtr;
};




#endif /* SOCKET_FILEOPERATOR_H_ */
