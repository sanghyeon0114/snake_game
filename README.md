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
3. 컴파일
```
g++ -Werror -std=c++11 -c *.cpp
```
4. 링크 ( 윈도우 )
```
g++ -o main.exe *.o
```
4-1. 링크 ( 리눅스 )
```
g++ -o main.exe *.o -lncurses
```

5. 실행
```
./main.exe
```
