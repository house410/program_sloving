#include <iostream>
#include <string>
#include <thread>
#include <regex> // 정규표현식 라이브러리 추가
#include <conio.h>
#include <Windows.h>

using namespace std;

// 로마자 문자를 아라비아 숫자로 변환하는 함수
int romanToArabic(char c) {
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0; // 유효하지 않은 문자 처리
    }
}


// 유효한 로마자 숫자인지 검사하는 함수
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
        cout << "로마자 숫자를 입력하세요 (종료하려면 esc 키를 누르세요): ";

        romanNum = _getch(); // 한 글자씩 입력 받음

        if (romanNum[0] != 27) { // esc 키가 입력되지 않았을 경우
            getline(cin, romanNum); // 나머지 문자열을 입력 받음
        }
        else {
            break; // esc 키가 입력되면 루프 종료
        }

        if (!isRomanNum(romanNum)) { // 로마자 숫자가 유효하지 않을 경우
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
            continue;
        }

        // 로마자 숫자를 아라비아 숫자로 변환하는 과정
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            if (romanToArabic(romanNum[i]) < romanToArabic(romanNum[i + 1])) { // 작은 수가 큰 수 앞에 오는 경우
                arabicNum -= romanToArabic(romanNum[i]);
            }
            else {
                arabicNum += romanToArabic(romanNum[i]);
            }
        }
        cout << "아라비아 숫자로 변환한 결과: " << arabicNum << endl;
    }
    return 0;
}

int main()
{
    thread inputThreadObj(inputThread); // 스레드 생성

    gameLoop(); // 메인 스레드에서 실행

    inputThreadObj.join(); // 스레드 종료 대기
    return 0;
}
