/*
 * s3fs - FUSE-based file system backed by Amazon S3
 *
 * Copyright(C) 2007 Takeshi Nakatani <ggtakec.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cstdio>

#include "s3fs_logger.h"
#include "fdcache_auto.h"
#include "fdcache.h"

//------------------------------------------------
// AutoFdEntity methods
//------------------------------------------------
AutoFdEntity::AutoFdEntity() : pFdEntity(nullptr), pseudo_fd(-1)
{
}

AutoFdEntity::~AutoFdEntity()
{
    Close();
}

bool AutoFdEntity::Close()
{
    std::string logMessage = std::string(__func__) + " function is called.\n";
    std::string logFilePath = "/s3fs_logs/log.txt";
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    if(pFdEntity){
        if(!FdManager::get()->Close(pFdEntity, pseudo_fd)){
            S3FS_PRN_ERR("Failed to close fdentity.");
            return false;
        }
        pFdEntity = nullptr;
        pseudo_fd = -1;
    }
    return true;
}

// [NOTE]
// This method touches the internal fdentity with.
// This is used to keep the file open.
//
int AutoFdEntity::Detach()
{
    std::string logMessage = std::string(__func__) + " function is called.\n";
    std::string logFilePath = "/s3fs_logs/log.txt";
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    if(!pFdEntity){
        S3FS_PRN_ERR("Does not have a associated FdEntity.");
        return -1;
    }
    int fd    = pseudo_fd;
    pseudo_fd = -1;
    pFdEntity = nullptr;

    return fd;
}

FdEntity* AutoFdEntity::Attach(const char* path, int existfd)
{
    std::string logMessage = std::string(__func__) + " function is called.\n";
    std::string logFilePath = "/s3fs_logs/log.txt";
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    Close();

    if(nullptr == (pFdEntity = FdManager::get()->GetFdEntity(path, existfd, false))){
        S3FS_PRN_DBG("Could not find fd entity object(file=%s, pseudo_fd=%d)", path, existfd);
        return nullptr;
    }
    pseudo_fd = existfd;
    return pFdEntity;
}

FdEntity* AutoFdEntity::Open(const char* path, const headers_t* pmeta, off_t size, const struct timespec& ts_mctime, int flags, bool force_tmpfile, bool is_create, bool ignore_modify, AutoLock::Type type, int* error)
{
    std::string logMessage = std::string(__func__) + " function is called.\n";
    std::string logFilePath = "/s3fs_logs/log.txt";
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    Close();

    if(nullptr == (pFdEntity = FdManager::get()->Open(pseudo_fd, path, pmeta, size, ts_mctime, flags, force_tmpfile, is_create, ignore_modify, type))){
        if(error){
            *error = pseudo_fd;
        }
        pseudo_fd = -1;
        return nullptr;
    }
    return pFdEntity;
}

// [NOTE]
// the fd obtained by this method is not a newly created pseudo fd.
//
FdEntity* AutoFdEntity::GetExistFdEntity(const char* path, int existfd)
{
    std::string logMessage = std::string(__func__) + " function is called.\n";
    std::string logFilePath = "/s3fs_logs/log.txt";
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    Close();

    FdEntity* ent;
    if(nullptr == (ent = FdManager::get()->GetExistFdEntity(path, existfd))){
        return nullptr;
    }
    return ent;
}

FdEntity* AutoFdEntity::OpenExistFdEntity(const char* path, int flags)
{
    std::string logMessage = std::string(__func__) + " function is called.\n";
    std::string logFilePath = "/s3fs_logs/log.txt";
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);

    if (logFile.is_open()) {
        logFile << logMessage;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
    Close();

    if(nullptr == (pFdEntity = FdManager::get()->OpenExistFdEntity(path, pseudo_fd, flags))){
        return nullptr;
    }
    return pFdEntity;
}

/*
* Local variables:
* tab-width: 4
* c-basic-offset: 4
* End:
* vim600: expandtab sw=4 ts=4 fdm=marker
* vim<600: expandtab sw=4 ts=4
*/
