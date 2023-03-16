#include <iostream>
#include <string>
#include <thread>
#include <regex> // ����ǥ���� ���̺귯�� �߰�
#include <conio.h>
#include <Windows.h>

using namespace std;

// �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� �Լ�
int romanToArabic(char c) {
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0; // ��ȿ���� ���� ���� ó��
    }
}


// ��ȿ�� �θ��� �������� �˻��ϴ� �Լ�
bool isRomanNum(string str) {
    regex pattern("^(M{0,3})(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");
    return regex_match(str, pattern);
}

string romanNum;
int arabicNum = 0;

void inputThread() {
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            exit(0);
        }
    }
}

int gameLoop() {

    while (true) {
        cout << "�θ��� ���ڸ� �Է��ϼ��� (�����Ϸ��� esc Ű�� ��������): ";

        romanNum = _getch(); // �� ���ھ� �Է� ����

        if (romanNum[0] != 27) { // esc Ű�� �Էµ��� �ʾ��� ���
            getline(cin, romanNum); // ������ ���ڿ��� �Է� ����
        }
        else {
            break; // esc Ű�� �ԷµǸ� ���� ����
        }

        if (!isRomanNum(romanNum)) { // �θ��� ���ڰ� ��ȿ���� ���� ���
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }

        // �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� ����
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            if (romanToArabic(romanNum[i]) < romanToArabic(romanNum[i + 1])) { // ���� ���� ū �� �տ� ���� ���
                arabicNum -= romanToArabic(romanNum[i]);
            }
            else {
                arabicNum += romanToArabic(romanNum[i]);
            }
        }
        cout << "�ƶ��� ���ڷ� ��ȯ�� ���: " << arabicNum << endl;
    }
    return 0;
}

int main()
{
    thread inputThreadObj(inputThread); // ������ ����

    gameLoop(); // ���� �����忡�� ����

    inputThreadObj.join(); // ������ ���� ���
    return 0;
}
