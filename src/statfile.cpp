#include "statfile.h"
#include <iostream>
#include <fstream>

FileUploadStats::FileUploadStats() : uploadCount(0), totalUploadTime(0), totalUploadSize(0), downloadCount(0), totalDownloadTime(0), totalDownloadSize(0) {}

void FileUploadStats::IncrementUploadCount() {
    uploadCount++;
}

void FileUploadStats::IncrementDownloadCount() {
    downloadCount++;
}

void FileUploadStats::UpdateUploadTimeStats(long uploadTime) {
    totalUploadTime += uploadTime;
}

void FileUploadStats::UpdateUploadSizeStats(long uploadSize) {
    totalUploadSize += uploadSize;
}

void FileUploadStats::UpdateDownloadStats(long downloadTime, long downloadSize) {
    totalDownloadTime += downloadTime;
    totalDownloadSize += downloadSize;
}

void FileUploadStats::PrintStats() {
    std::cout << "Upload Stats: Count = " << uploadCount
              << ", Total Time = " << totalUploadTime
              << ", Total Size = " << totalUploadSize << std::endl;

    std::cout << "Download Stats: Count = " << downloadCount
              << ", Total Time = " << totalDownloadTime
              << ", Total Size = " << totalDownloadSize << std::endl;
              
}

void FileUploadStats::PrintStatsToFile(const std::string& filename) {
    std::ofstream outfile(filename);  // 출력 파일 스트림 생성

    if (outfile.is_open()) {
        outfile << "Upload Stats: Count = " << uploadCount
                << ", Total Time = " << totalUploadTime
                << ", Total Size = " << totalUploadSize << std::endl;

        outfile << "Download Stats: Count = " << downloadCount
                << ", Total Time = " << totalDownloadTime
                << ", Total Size = " << totalDownloadSize << std::endl;

        // 파일 닫기
        outfile.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

// ...



FileUploadStats StatFile::fileStats;

void StatFile::IncrementUploadCount() {
    fileStats.IncrementUploadCount();
}

void StatFile::IncrementDownloadCount() {
    fileStats.IncrementDownloadCount();
}

void StatFile::UpdateUploadTimeStats(long uploadTime) {
    fileStats.UpdateUploadTimeStats(uploadTime);
}

void StatFile::UpdateUploadSizeStats(long uploadSize) {
    fileStats.UpdateUploadSizeStats(uploadSize);
}

void StatFile::UpdateDownloadStats(long downloadTime, long downloadSize) {
    fileStats.UpdateDownloadStats(downloadTime, downloadSize);
}

void StatFile::PrintStats() {
    fileStats.PrintStats();
}

void StatFile::PrintStatsToFile(const std::string& filename) {
    fileStats.PrintStatsToFile(filename);
}
