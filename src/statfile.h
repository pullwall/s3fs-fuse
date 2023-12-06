#ifndef STATFILE_H
#define STATFILE_H
#include <string>

class FileUploadStats {
public:
    long uploadCount;
    long totalUploadTime;
    long totalUploadSize;

    long downloadCount;
    long totalDownloadTime;
    long totalDownloadSize;

    FileUploadStats();

    void IncrementUploadCount();

    void IncrementDownloadCount();

    void UpdateUploadTimeStats(long uploadTime);

    void UpdateUploadSizeStats(long uploadSize);

    void UpdateDownloadStats(long downloadTime, long downloadSize);

    void PrintStats();

    void PrintStatsToFile(const std::string& filename);
};

class StatFile {
public:
    static FileUploadStats fileStats;

    static void IncrementUploadCount();

    static void IncrementDownloadCount();

    static void UpdateUploadTimeStats(long uploadTime);

    static void UpdateUploadSizeStats(long uploadSize);

    static void UpdateDownloadStats(long downloadTime, long downloadSize);

    static void PrintStats();

    static void PrintStatsToFile(const std::string& filename);
};

#endif // STATFILE_H
