#pragma once

#include <string>
#include <sstream>

namespace lib::utils
{
  class TextParse
  {
  public:
    TextParse(std::string text)
    {
      Text = text;
    }

    void add(std::string key, std::string value)
    {
      Text += "\n" + key + "|" + value;
    }

    static std::vector<std::string> vectorize(std::string str)
    {
      std::istringstream varStream(str);
      std::vector<std::string> vec;
      std::string token;
      while (std::getline(varStream, token, '|'))
      {
        vec.push_back(token);
      }
      return vec;
    }

  public:
    std::string Text;
  };
}