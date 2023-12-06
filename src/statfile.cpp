//statefile.cpp



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
    StatFile() : uploadCount(0), downloadCount(0), startTime(std::chrono::steady_clock::now()) {
        // 파일 출력 스트림 초기화
        outputFile.open("stats.txt", std::ios::out | std::ios::app);

        std::cout << "StatFile instance created." << std::endl;
    }

    ~StatFile() {
        // 파일 출력 스트림 닫기
        outputFile.close();

        // 여기에서 파일 저장 또는 정리 로직 수행 가능
        std::cout << "StatFile instance destroyed." << std::endl;
    }

    // 복사 생성자와 대입 연산자를 private으로 선언하여 복사를 방지
    StatFile(const StatFile&) = delete;
    StatFile& operator=(const StatFile&) = delete;

public:
    // 정적 메서드를 통해 유일한 인스턴스에 접근
    static StatFile& getInstance() {
        // 정적 지역 변수을 사용하여 최초 호출 시에만 인스턴스를 생성
        static StatFile instance;
        return instance;
    }

    // 파일 업로드 횟수 증가 및 누적 시간 업데이트
    void uploadFile(const std::string& filePath) {
        uploadCount++;
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        // 여기에서 파일 업로드 통계 정보 업데이트 로직 수행 가능
        std::cout << "Uploaded file: " << filePath << ", Elapsed Time: " << elapsedTime << " ms" << std::endl;

        // 파일에 통계 정보 저장
        outputFile << "Uploaded file: " << filePath << ", Elapsed Time: " << elapsedTime << " ms" << std::endl;
    }

    // 파일 다운로드 횟수 증가 및 누적 시간 업데이트
    void downloadFile(const std::string& filePath) {
        downloadCount++;
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        // 여기에서 파일 다운로드 통계 정보 업데이트 로직 수행 가능
        std::cout << "Downloaded file: " << filePath << ", Elapsed Time: " << elapsedTime << " ms" << std::endl;

        // 파일에 통계 정보 저장
        outputFile << "Downloaded file: " << filePath << ", Elapsed Time: " << elapsedTime << " ms" << std::endl;
    }

    // 평균 업로드 및 다운로드 시간 출력
    void printAverageStats() const {
        auto endTime = std::chrono::steady_clock::now();
        auto totalElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        // 평균 시간 계산
        double averageUploadTime = uploadCount > 0 ? static_cast<double>(totalElapsedTime) / uploadCount : 0.0;
        double averageDownloadTime = downloadCount > 0 ? static_cast<double>(totalElapsedTime) / downloadCount : 0.0;

        std::cout << "Average Upload Time: " << averageUploadTime << " ms" << std::endl;
        std::cout << "Average Download Time: " << averageDownloadTime << " ms" << std::endl;

        // 파일에 평균 통계 정보 저장
        outputFile << "Average Upload Time: " << averageUploadTime << " ms" << std::endl;
        outputFile << "Average Download Time: " << averageDownloadTime << " ms" << std::endl;
    }
};
