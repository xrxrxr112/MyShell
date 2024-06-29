// MyShell.cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <vector>
#include <string>

#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define SEPARATOR " \t\n"

extern char **environ; // 声明环境变量

// executeScript 函数声明
bool executeScript(const char* scriptPath);

int main(int argc, char** argv)
{
    const char* prompt = "==>";
    char linebuf[MAX_BUFFER];
    char cmndbuf[MAX_BUFFER];
    char *args[MAX_ARGS] = {0}; // 初始化 args 数组
    char *arg;

    while (true)
    {
        std::cout << prompt << std::flush;

        // 检查输入
        if (!fgets(linebuf, MAX_BUFFER, stdin))
        {
            if (feof(stdin))
            {
                std::cout << "EOF encountered. Exiting..." << std::endl;
                break;
            }
            else
            {
                std::perror("Error reading from stdin");
                continue;
            }
        }

        // 分割命令行参数
        arg = strtok(linebuf, SEPARATOR);
        int argIndex = 0;
        while (arg != NULL && argIndex < MAX_ARGS - 1)
        {
            args[argIndex++] = arg;
            arg = strtok(NULL, SEPARATOR);
        }
        args[argIndex] = NULL; // 确保最后一个参数是 NULL

        // 执行命令
        if (args[0] != NULL)
        {
            switch (args[0][0])
            {
                // 清屏命令
                case 'c':
                    system("clear");
                    break;

                // 列出目录内容命令
                case 'l':
                    if (strcmp(args[0], "ls") == 0)
                    {
                        snprintf(cmndbuf, sizeof(cmndbuf), "ls %s", (args[1] ? args[1] : "."));
                        system(cmndbuf);
                    }
                    break;

                // 显示环境变量命令
                case 'e':
                    if (strcmp(args[0], "environ") == 0)
                    {
                        for (char **envstr = environ; *envstr; ++envstr)
                        {
                            std::cout << *envstr << std::endl;
                        }
                    }
                    if (strcmp(args[0], "echo") == 0)
                    {
                        for (int i = 1; i < argIndex; ++i)
                        {
                            std::cout << args[i];
                            if (i < argIndex - 1)
                                std::cout << " ";
                        }
                        std::cout << std::endl;
                    }
                    break;

                // 执行脚本命令
                case 's':
                    if (strcmp(args[0], "script") == 0 && args[1] != NULL)
                    {
                        if (!executeScript(args[1]))
                        {
                            std::cerr << "Error executing script: " << args[1] << std::endl;
                        }
                        else
                        {
                            std::cout << "Script executed successfully." << std::endl;
                        }
                    }
                    break;

                // 退出命令
                case 'q':
                    break;
                //     if (strcmp(args[0], "quit") == 0)
                //     {
                //         std::cout << "Exiting MyShell..." << std::endl;
                //         break;
                //     }

                // 默认其他命令
                default:
                    snprintf(cmndbuf, sizeof(cmndbuf), "%s", args[0]);
                    for (int i = 1; args[i] != NULL; ++i)
                    {
                        strcat(cmndbuf, " ");
                        strcat(cmndbuf, args[i]);
                    }
                    system(cmndbuf);
                    break;
            }
            if (strcmp(args[0], "quit") == 0)
            {
                std::cout << "Exiting MyShell..." << std::endl;
                break;
            }
        }
    }
    return 0;
}

// executeScript 函数定义
bool executeScript(const char* scriptPath)
{
    std::ifstream scriptFile(scriptPath);
    if (!scriptFile.is_open())
    {
        std::cerr << "Cannot open script file: " << scriptPath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(scriptFile, line))
    {
        // 忽略空行和注释行
        if (line.empty() || line.substr(0, 1) == "#")
            continue;

        // 执行脚本中的命令
        int ret = system(line.c_str());
        if (ret != 0)
        {
            std::cerr << "Command failed in script: " << line << std::endl;
            scriptFile.close();
            return false;
        }
    }

    scriptFile.close();
    return true;
}




