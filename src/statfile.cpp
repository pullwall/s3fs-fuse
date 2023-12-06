#include "statfile.h"
#include <iostream>
#include <fstream>
#include <string>

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

void FileUploadStats::UpdateDownloadTimeStats(long downloadTime) {
    totalDownloadTime += downloadTime;
}

void FileUploadStats::UpdateDownloadSizeStats(long downloadSize) {
    totalDownloadSize += downloadSize;
}

void FileUploadStats::PrintStatsToFile(const std::string& filename) {
    std::ofstream outfile(filename);  // 출력 파일 스트림 생성

    if (outfile.is_open()) {
        // 업로드 관련 통계
        outfile << "Upload Stats: Count = " << uploadCount
                << ", Total File Upload Time = " << totalUploadTime
                << ", Total File Upload Size = " << totalUploadSize
                << ", Average Upload Speed = " << (totalUploadTime > 0 ? totalUploadSize / totalUploadTime : 0) << " bytes per second"
                << std::endl;

        // 다운로드 관련 통계
        outfile << "Download Stats: Count = " << downloadCount
                << ", Total File Download Time = " << totalDownloadTime
                << ", Total File Download Size = " << totalDownloadSize
                << ", Average Download Speed = " << (totalDownloadTime > 0 ? totalDownloadSize / totalDownloadTime : 0) << " bytes per second"
                << std::endl;

        // 파일 닫기
        outfile.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}



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

void StatFile::UpdateDownloadTimeStats(long downloadTime) {
    fileStats.UpdateDownloadTimeStats(downloadTime);
}

void StatFile::UpdateDownloadSizeStats(long downloadSize) {
    fileStats.UpdateDownloadSizeStats(downloadSize);
}

void StatFile::PrintStatsToFile(const std::string& filename) {
    fileStats.PrintStatsToFile(filename);
}
