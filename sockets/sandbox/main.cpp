#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;
void decode(string text) {
  // string text ="{\"1\":{\"name\":\"MIKE\",\"surname\":\"TAYLOR\"},\"2\":{\"name\":\"TOM\",\"surname\":\"JERRY\"}}";

  Json::CharReaderBuilder builder;
  Json::CharReader * reader = builder.newCharReader();

  Json::Value root;
  string errors;

  bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);
  delete reader;

  if ( !parsingSuccessful )
  {
    cout << text << endl;
    cout << errors << endl;
  }

  for( Json::Value::const_iterator outer = root.begin() ; outer != root.end() ; outer++ )
  {
    for( Json::Value::const_iterator inner = (*outer).begin() ; inner!= (*outer).end() ; inner++ )
    {
      cout << inner.key() << ": " << *inner << endl;
    }
  }
}
int main () {
    // ifstream ifs("profile.json");
    // Json::Reader reader;
    // Json::Value obj;
    // reader.parse(ifs, obj);
    // cout << "Last name: " << obj["lastname"].asString() << endl;
    // cout << "First name: " << obj["firstname"].asString() << endl;
  string text ="{\"1\":{\"name\":\"MIKE\",\"surname\":\"TAYLOR\"},\"2\":{\"name\":\"TOM\",\"surname\":\"JERRY\"}}";
  decode(text);













  //
  // // std::string s = "scott>=tiger>=mushroom";
  // std::string delimiter = ":";
  //
  // size_t pos = 0;
  // std::string token;
  // while ((pos = s.find(delimiter)) != std::string::npos) {
  //     token = s.substr(0, pos);
  //     std::cout << token << std::endl;
  //     s.erase(0, pos + delimiter.length());
  // }
  // s = s.substr(0, s.size()-1);
  // int status = stoi(s);
  // std::cout << status << std::endl;
  //
  // // int status;
  // // status = stoi(message);
  // // cout << status << endl;




































  // string ei = "stoel";
  // int status = 1;
  // string bericht = ei + " : " + to_string(ja);
  // cout << "Hele bericht: " << bericht << endl;

  // string delimiter = ":";
  // int index = 0;
  // string id;
  //
  // while ((index = message.find(delimiter)) != std::string::npos) {
  //     id = message.substr(0, index);
  //     message.erase(0, index + delimiter.length());
  // }
  // int status_conv = stoi(message);
  // cout << status_conv << endl;




  // Json j;
  // cout << j.split(message) << endl;
  // cout << j.to_int(message) << endl;
// -------------------------------------------------
  // cout << split(message) << endl;
  // cout << to_int(message) << endl;

  return 0;
}
