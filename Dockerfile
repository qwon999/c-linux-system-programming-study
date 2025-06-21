# 베이스 이미지를 ubuntu 최신 버전으로 지정합니다.
FROM ubuntu:latest

# apt-get install 실행 시 대화형 프롬프트가 뜨는 것을 방지합니다.
ENV DEBIAN_FRONTEND=noninteractive

# 우분투 패키지 리스트를 업데이트하고,
# C/C++ 개발에 필요한 핵심 도구들을 모두 설치합니다.
# -y 옵션은 설치 과정 중 모든 질문에 자동으로 'yes'라고 답해줍니다.
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb

# build-essential: C/C++ 컴파일러(gcc, g++)와 make 등 필수 도구 모음
# cmake: CLion이 프로젝트를 빌드하기 위해 사용하는 도구
# gdb: C/C++ 코드를 디버깅하기 위한 도구
