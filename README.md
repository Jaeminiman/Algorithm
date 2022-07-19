# Algorithm
1. 백준 매 주 8문제 push
2. 알고리즘 문제 해결 전략 매주 1 ~ 2장 개인 학습

## 전체 스케쥴
- 15개 주제   

- 매주 목요일 16:00 - 19:00  

<07/06> 6 7  
<07/13> 8 9   
<07/20> 10 11  
<07/27> 12 13  
<08/03> 14 15  
<08/10> 27 28  
<08/17> 29 30  
<08/24> 31 32  
<08/31>  

## git 설정 방법
1. local 폴더 만들어서 Terminal로 해당 폴더 접근
2. git init
3. git clone https://github.com/Jaeminiman/Algorithm.git
4. 원본 프로젝트 저장소를 원격 저장소로 추가
  $ git remote add origin https://github.com/Jaeminiman/Algorithm.git
  원격 저장소 설정 현황 확인방법
  $ git remote -v
5. branch 생성
  ex) develop 이라는 이름의 branch를 생성한다.
  $ git checkout -b [branch 이름]
6. 작업할 branch로 이동
  $ git checkout [branch 이름]

## github에 올리는 법
1. git add [파일명] or git add .(전체 올릴 때)
2. git commit -m "원하는 메시지"
3. git push origin [branch 이름]
