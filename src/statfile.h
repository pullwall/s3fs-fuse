//statefile.h


#ifndef STATFILE_H
#define STATFILE_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

class StatFile {
private:
    int uploadCount;
    int downloadCount;
    std::chrono::steady_clock::time_point startTime;
    std::ofstream outputFile;  // 파일 출력 스트림

    // 생성자와 소멸자를 private으로 선언하여 외부에서 객체 생성 및 소멸을 방지
    StatFile();
    ~StatFile();

    // 복사 생성자와 대입 연산자를 private으로 선언하여 복사를 방지
    StatFile(const StatFile&) = delete;
    StatFile& operator=(const StatFile&) = delete;

public:
    // 정적 메서드를 통해 유일한 인스턴스에 접근
    static StatFile& getInstance();

    // 파일 업로드 횟수 증가 및 누적 시간 업데이트
    void uploadFile(const std::string& filePath);

    // 파일 다운로드 횟수 증가 및 누적 시간 업데이트
    void downloadFile(const std::string& filePath);

    // 평균 업로드 및 다운로드 시간 출력
    void printAverageStats() const;
};

#endif // STATFILE_H
