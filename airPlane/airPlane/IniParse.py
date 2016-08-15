#!/usr/bin/python

import sys,os,time
import ConfigParser
def read_config(config_file_path, field, key):
    config = ConfigParser.ConfigParser()
    config.readfp(open(config_file_path))
    result = config.get(field,key)
    return  result


def write_config(config_file_path, field, key, value):
    config = ConfigParser.ConfigParser()
    config.write(open(config_file_path, "w"))


if __name__ == "__main__":
    config_file_path="INTERVAL.cfg"
    field="AIRPLANE"
    key = "INTERVAL"
    if os.path.exists(config_file_path):
        value =  read_config(config_file_path, field, key)
        print "read success !"
    else:
        print "No file"

    if len(sys.argv) < 2:
        print "No target Dir"
        sys.exit(1)
    index = 1
    targetdir = sys.argv[1]
    while True:

        strindex = str(index)

        inifile = strindex + ".ini"
        picfile = strindex + ".jpeg"
        if os.path.exists(inifile) or os.path.exists(picfile):
            cmdmsg = 'cp -r -f /' + str(inifile) + '  /' + str(picfile) + ' '+ targetdir
            print cmdmsg
        else:
            print "No files"
            time.sleep(int(value))
            continue
        index = index + 1
        os.system(str(cmdmsg))
        time.sleep(int(value))

