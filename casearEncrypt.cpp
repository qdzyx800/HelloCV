#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Crypto {
public:
    static string caesarEncrypt(const string& text, int key) {
        string result = "";
        for (char c : text) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + key) % 26 + base;
            }
            result += c;
        }
        return result;
    }

    static string caesarDecrypt(const string& text, int key) {
        return caesarEncrypt(text, 26 - key);
    }
};

class FileHandler {
public:
    static string readFile(const string& filename) {
        ifstream file(filename);
        string content((istreambuf_iterator<char>(file)), 
                      istreambuf_iterator<char>());
        return content;
    }

    static void writeFile(const string& filename, const string& content) {
        ofstream file(filename);
        file << content;
    }
};

class Menu {
public:
    void show() {
        while (true) {
            cout << "\n=== 简易文本加密解密工具 ===" << endl;
            cout << "1. 文本加密" << endl;
            cout << "2. 文本解密" << endl;
            cout << "3. 文件加密" << endl;
            cout << "4. 文件解密" << endl;
            cout << "5. 退出" << endl;
            cout << "请选择功能: ";
            
            int choice;
            cin >> choice;
            cin.ignore(); // 清除换行符
            
            switch (choice) {
                case 1: textEncrypt(); break;
                case 2: textDecrypt(); break;
                case 3: fileEncrypt(); break;
                case 4: fileDecrypt(); break;
                case 5: return;
                default: cout << "无效选择！" << endl;
            }
        }
    }

private:
    void textEncrypt() {
        string text, encrypted;
        int key;
        
        cout << "请输入要加密的文本: ";
        getline(cin, text);
        cout << "请输入密钥: ";
        cin >> key;
        
        encrypted = Crypto::caesarEncrypt(text, key);
        cout << "加密结果: " << encrypted << endl;
    }

    void textDecrypt() {
        string text, decrypted;
        int key;
        
        cout << "请输入要解密的文本: ";
        getline(cin, text);
        cout << "请输入密钥: ";
        cin >> key;
        
        decrypted = Crypto::caesarDecrypt(text, key);
        cout << "解密结果: " << decrypted << endl;
    }

    void fileEncrypt() {
        string inputFile, outputFile, content, encrypted;
        int key;
        
        cout << "请输入要加密的文件路径: ";
        getline(cin, inputFile);
        cout << "请输入密钥: ";
        cin >> key;
        
        content = FileHandler::readFile(inputFile);
        encrypted = Crypto::caesarEncrypt(content, key);
        
        outputFile = "encrypted_" + inputFile;
        FileHandler::writeFile(outputFile, encrypted);
        cout << "加密结果已保存到: " << outputFile << endl;
    }

    void fileDecrypt() {
        string inputFile, outputFile, content, decrypted;
        int key;
        
        cout << "请输入要解密的文件路径: ";
        getline(cin, inputFile);
        cout << "请输入密钥: ";
        cin >> key;
        
        content = FileHandler::readFile(inputFile);
        decrypted = Crypto::caesarDecrypt(content, key);
        
        outputFile = "decrypted_" + inputFile;
        FileHandler::writeFile(outputFile, decrypted);
        cout << "解密结果已保存到: " << outputFile << endl;
    }
};

int main() {
    Menu menu;
    menu.show();
    return 0;
}