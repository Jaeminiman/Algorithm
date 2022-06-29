# Algorithm
Study_Backjoon

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

