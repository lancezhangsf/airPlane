#include <iostream>
#include "Logger.h"
using namespace std;
using namespace FrameWork;
int
main(int argc,char* argv[])
{
  InitLogging(argv[0],INFO,"./log/test");
  cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
  LOG(INFO) << "info test";
  LOG(WARN) << "WARN TEST %d" << 20;
  LOG(ERROR) << "Error test %d %s" << 20 << "nihao";

  Logger::GetInstance().Error("error test common");
  Logger::GetInstance().Fatal("fatal test common ");
  Logger::GetInstance().Fatal("fatal test common %d ",100);
  Logger::GetInstance().Info("info test normal %d %s ",50,"zhongguoren");
  Logger::GetInstance().Info("info test normal ");
  return 0;
}
