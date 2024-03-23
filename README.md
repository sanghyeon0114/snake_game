# 빌드 방법

아래 명령어를 따라 치시면 됩니다.

1. git clone 을 통해 코드 받아오기

```
git clone https://github.com/sanghyeon0114/snake_game snake
```

2. snake 경로로 이동하기
```
cd snake
```
3. BOARD SIZE와 MOVE DELAY 설정.

main.cpp에 있는 전처리기 변수 BOARD_SIZE와 MOVE_DELAY를 수정해서 사용하세요.

BOARD_SIZE는 게임의 맵 크기를 설정합니다. 4부터 20까지 설정할 수 있습니다.

MOVE_DELAY는 뱀의 프레임 수를 설정합니다. 15로 설정하면, 15프레임마다 1번씩 뱀이 움직입니다!

4. 컴파일
```
g++ -Werror -std=c++11 -c *.cpp
```
5. 링크 ( 윈도우 )
```
g++ -o main.exe *.o
```
5-1. 링크 ( 리눅스 )
```
g++ -o main.exe *.o -lncurses
```

6. 실행
```
./main.exe
```
