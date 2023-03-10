#include <iostream>
#include <string>
#include <conio.h>

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

string romanNum; // 사용자로부터 입력 받은 로마자 숫자
int arabicNum = 0; // 로마자 숫자를 아라비아 숫자로 변환한 결과

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

        if (romanNum.empty()) { // 입력 오류 처리
            cout << "입력 오류입니다. 프로그램을 종료합니다." << endl;
            return 1;
        }

        // 로마자 숫자를 아라비아 숫자로 변환하는 과정
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            if (romanToArabic(romanNum[i]) == 0) { // 유효하지 않은 문자 처리
                cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
                break;
            }
            if (i < romanNum.length() - 1 && romanToArabic(romanNum[i]) < romanToArabic(romanNum[i + 1])) {
                arabicNum -= romanToArabic(romanNum[i]); // 작은 수가 큰 수 앞에 오는 경우
            }
            else {
                arabicNum += romanToArabic(romanNum[i]);
            }
        }
        cout << "아라비아 숫자로 변환한 결과: " << arabicNum << endl;
    }
}


int main() {

    gameLoop();

    return 0;
}