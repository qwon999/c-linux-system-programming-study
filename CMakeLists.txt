# CMake 최소 요구 버전 설정
cmake_minimum_required(VERSION 3.20)

# 프로젝트 이름과 언어 설정
project(c_linux_study C)

# C 표준을 C11로 설정
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 컴파일 경고 옵션 활성화 (-Wall 옵션과 동일)
add_compile_options(-Wall)

# ================================================================
# 문제 풀이(PS) 폴더 자동화 설정
# PS 폴더 내의 모든 .c 파일을 찾아 자동으로 실행 파일을 생성합니다.
# ================================================================

# PS 폴더가 존재하는지 확인합니다.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/PS")

    # "PS" 폴더 내의 모든 .c 파일 목록을 가져와 'ps_sources'라는 변수에 저장합니다.
    file(GLOB ps_sources "PS/*.c")

    # 'ps_sources' 변수에 담긴 각 소스 파일에 대해 반복문을 실행합니다.
    foreach(source_file ${ps_sources})

        # 소스 파일의 전체 경로에서 파일 이름과 확장자를 제외한 순수 이름만 추출합니다.
        # 예: "PS/10818.c" -> "10818"
        get_filename_component(executable_name ${source_file} NAME_WE)

        # 추출한 이름으로 실행 파일을 생성하도록 add_executable을 동적으로 추가합니다.
        # 예: add_executable(10818 PS/10818.c)
        add_executable(${executable_name} ${source_file})

    endforeach()

endif()




# "hello_world" 라는 이름의 실행 파일을 main.c 소스 파일로부터 생성
# 나중에 다른 파일을 만들면 이 부분을 추가하거나 수정하면 됩니다.
add_executable(hello_world main.c)

# 1주차 실습 과제를 위한 실행 파일들을 정의.
# 각 add_executable 줄은 "실행파일_이름" "소스파일.c" 형식.
add_executable(hello_world_day1 Day1_pointer_memory/main.c)
add_executable(memory_layout Day1_pointer_memory/memory_layout.c)
add_executable(swap_test Day1_pointer_memory/swap_test.c)

# 2주차 실습 과제를 위한 실행 파일들을 정의.
add_executable(my_string_test Day2_pointer_array_fileio/my_string_test.c)
add_executable(my_cat Day2_pointer_array_fileio/my_cat.c)
add_executable(my_cp Day2_pointer_array_fileio/my_cp.c)

# 3주차 실습 과제를 위한 실행 파일들을 정의.
add_executable(fork_test Day3_process_management/fork_test.c)
add_executable(exec_test Day3_process_management/exec_test.c)
add_executable(wait_test Day3_process_management/wait_test.c)
add_executable(mini_shell Day3_process_management/mini_shell.c)

