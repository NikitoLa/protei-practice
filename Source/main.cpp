//#include "functions.hpp"

#include <benchmark/benchmark.h>

#include <regex>
#include <re2/re2.h>
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace boost::xpressive;

std::vector<std::string> readFromfile(std::string path)
{
  std::vector<std::string> v;
  std::ifstream fin;
  std::string str;
  fin.open(path);
  try
  {
    fin.is_open();
    // if (fin.is_open())
    // {
    //   std::cout << "file opend succsesfully" << std::endl;
    // }
    // else
    // {
    //   std::cout << "file opend EROROROROROR" << std::endl;
    // }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  while (!fin.eof())
  {
    std::getline(fin, str);
    v.push_back(str);
  }
  fin.close();
  return v;
}

bool FindReg(std::string str, std::regex reg_expression) {
  return std::regex_match(str, reg_expression);
}

bool FindRe2(std::string str, std::string reg_expression) {
  return RE2::PartialMatch(str, reg_expression);
}

bool FindBoost(std::string str, boost::regex reg_expression) {
  return boost::regex_match(str, reg_expression);
}

bool FindXpressive(std::string str, sregex reg_expression) {
  return regex_match(str, reg_expression);
}

// static void BM_stdRegex(benchmark::State& state) {
//   std::vector<std::string> regulars = readFromfile("/home/nikitola/Documents/Practice/reg.txt");
//   std::vector<std::string> test_strings = readFromfile("/home/nikitola/Documents/Practice/teststrings.txt");
//   for (auto _ : state) {
//     // This code gets timed
//     for (int i = 0; i < regulars.size(); i++)
//     {
//       for (int j = 0; j < 4; j++)
//       {
//         FindReg(test_strings[4*i+j], std::regex(regulars[i]));
//       }
//     }
//   }
// }
// static void BM_re2(benchmark::State& state) {
//   // Perform setup here
//   std::vector<std::string> regulars = readFromfile("/home/nikitola/Documents/Practice/reg.txt");
//   std::vector<std::string> test_strings = readFromfile("/home/nikitola/Documents/Practice/teststrings.txt");
//   for (auto _ : state) {
//     // This code gets timed
//     for (int i = 0; i < regulars.size(); i++)
//     {
//       for (int j = 0; j < 4; j++)
//       {
//         FindRe2(test_strings[4*i+j], regulars[i]);
//       }
//     }
//   }
// }
// static void BM_boost(benchmark::State& state) {
//   // Perform setup here
//   std::vector<std::string> regulars = readFromfile("/home/nikitola/Documents/Practice/reg.txt");
//   std::vector<std::string> test_strings = readFromfile("/home/nikitola/Documents/Practice/teststrings.txt");
//   for (auto _ : state) {
//     // This code gets timed
//     for (int i = 0; i < regulars.size(); i++)
//     {
//       for (int j = 0; j < 4; j++)
//       {
//         FindBoost(test_strings[4*i+j], boost::regex(regulars[i]));
//       }
//     }
//   }
// }
// static void BM_xpressive(benchmark::State& state) {
//   // Perform setup here
//   std::vector<std::string> regulars = readFromfile("/home/nikitola/Documents/Practice/reg.txt");
//   std::vector<std::string> test_strings = readFromfile("/home/nikitola/Documents/Practice/teststrings.txt");
//   for (auto _ : state) {
//     // This code gets timed
//     for (int i = 0; i < regulars.size(); i++)
//     {
//       for (int j = 0; j < 4; j++)
//       {
//         FindXpressive(test_strings[4*i+j], sregex::compile(regulars[i]));
//       }
//     }
//   }
// }

// Register the function as a benchmark
// BENCHMARK(BM_stdRegex)->Name("Std::regex")->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_re2)->Name("re2")->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_boost)->Name("boost")->Unit(benchmark::kMillisecond);
// BENCHMARK(BM_xpressive)->Name("xpressive")->Unit(benchmark::kMillisecond);
// // BENCHMARK(BM_pcre2)->Name("pcre2");
// // Run the benchmark
// BENCHMARK_MAIN();

class MyFixture : public benchmark::Fixture
{
public:
    // add members as needed
    
    MyFixture()
    {
        std::cout << "Ctor only called once per fixture testcase hat uses it" << std::endl;
        regulars = readFromfile("/home/nikitola/Documents/Practice/reg.txt");
        test_strings = readFromfile("/home/nikitola/Documents/Practice/teststrings.txt");
    }

    std::vector<std::string> regulars;
    std::vector<std::string> test_strings;
};

BENCHMARK_F(MyFixture, stdRegex)(benchmark::State& state)
{
    //std::cout << "Benchmark function called more than once" << std::endl;
    for (auto _ : state)
    {
      for (int i = 0; i < regulars.size(); i++)
      {
        for (int j = 0; j < 4; j++)
        {
          FindReg(test_strings[4*i+j], std::regex(regulars[i]));
        }
      }
    }
}

BENCHMARK_F(MyFixture, re2)(benchmark::State& state)
{
    //std::cout << "Benchmark function called more than once" << std::endl;
    for (auto _ : state)
    {
      for (int i = 0; i < regulars.size(); i++)
      {
        for (int j = 0; j < 4; j++)
        {
          FindRe2(test_strings[4*i+j], regulars[i]);
        }
      }
    }
}

BENCHMARK_F(MyFixture, boost)(benchmark::State& state)
{
    //std::cout << "Benchmark function called more than once" << std::endl;
    for (auto _ : state)
    {
      for (int i = 0; i < regulars.size(); i++)
      {
        for (int j = 0; j < 4; j++)
        {
          FindBoost(test_strings[4*i+j], boost::regex(regulars[i]));
        }
      }
    }
}

BENCHMARK_F(MyFixture, xpression)(benchmark::State& state)
{
    //std::cout << "Benchmark function called more than once" << std::endl;
    for (auto _ : state)
    {
      for (int i = 0; i < regulars.size(); i++)
      {
        for (int j = 0; j < 4; j++)
        {
          FindXpressive(test_strings[4*i+j], sregex::compile(regulars[i]));
        }
      }
    }
}

// BENCHMARK_DEFINE_F(MyFixture, xpression)(benchmark::State& state)
// {
//     //std::cout << "Benchmark function called more than once" << std::endl;
//     for (auto _ : state)
//     {
//       for (int i = 0; i < regulars.size(); i++)
//       {
//         for (int j = 0; j < 4; j++)
//         {
//           FindXpressive(test_strings[4*i+j], sregex::compile(regulars[i]));
//         }
//       }
//     }
// }
// BENCHMARK_REGISTER_F(MyFixture, xpression)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();