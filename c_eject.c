#include <windows.h>
#include <stdio.h>

HANDLE OpenVolume(
    char cDriveLetter)
{
    char szRootName[5];
    wsprintf(
        szRootName,
        TEXT("%c:\\"),
        cDriveLetter);

    DWORD dwAccessFlags;

    UINT uDriveType = GetDriveType(szRootName);

    switch (uDriveType) {
    case DRIVE_REMOVABLE:
        dwAccessFlags = GENERIC_READ | GENERIC_WRITE;
        break;

    case DRIVE_CDROM:
        dwAccessFlags = GENERIC_READ;
        break;

    default:
        printf(
            TEXT("Cannot eject. Drive type is incorrect.\n"));
        return INVALID_HANDLE_VALUE;
    }

    char szVolumeName[8];

    wsprintf(
        szVolumeName,
        TEXT("\\\\.\\%c:"),
        cDriveLetter);

    HANDLE hVolume;
    hVolume = CreateFile(
        szVolumeName,
        dwAccessFlags,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hVolume == INVALID_HANDLE_VALUE)
        printf(
            TEXT("Error %d: %s\n"),
            GetLastError(),
            TEXT("CreateFile"));

    return hVolume;
}

BOOL LockVolume(
    HANDLE hVolume)
{
    DWORD dwBytesReturned;
    DWORD dwSleepAmount;
    int nTryCount;

    int nLockRetries = 20;

    dwSleepAmount = 10000 / nLockRetries;

    for (nTryCount = 0; nTryCount < nLockRetries; nTryCount++) {
        if (DeviceIoControl(
                hVolume,
                FSCTL_LOCK_VOLUME,
                NULL, 0,
                NULL, 0,
                &dwBytesReturned,
                NULL))
            return TRUE;

        Sleep(dwSleepAmount);
    }

    return FALSE;
}

BOOL DismountVolume(
    HANDLE hVolume)
{
    DWORD dwBytesReturned;

    return DeviceIoControl(
        hVolume,
        FSCTL_DISMOUNT_VOLUME,
        NULL, 0,
        NULL, 0,
        &dwBytesReturned,
        NULL);
}

BOOL PreventRemovalOfVolume(
    HANDLE hVolume,
    BOOL fPreventRemoval)
{
    DWORD dwBytesReturned;
    PREVENT_MEDIA_REMOVAL PMRBuffer;

    PMRBuffer.PreventMediaRemoval = fPreventRemoval;

    return DeviceIoControl(
        hVolume,
        IOCTL_STORAGE_MEDIA_REMOVAL,
        &PMRBuffer,
        sizeof(PREVENT_MEDIA_REMOVAL),
        NULL, 0,
        &dwBytesReturned,
        NULL);
}

BOOL AutoEjectVolume(
    HANDLE hVolume)
{
    DWORD dwBytesReturned;

    return DeviceIoControl(
        hVolume,
        IOCTL_STORAGE_EJECT_MEDIA,
        NULL, 0,
        NULL, 0,
        &dwBytesReturned,
        NULL);
}

BOOL EjectVolume(
    char cDriveLetter)
{
    HANDLE hVolume = OpenVolume(cDriveLetter);
    if (hVolume == INVALID_HANDLE_VALUE)
        return FALSE;

    BOOL fRemoveSafely = FALSE;
    BOOL fAutoEject = FALSE;

    if (LockVolume(hVolume) && DismountVolume(hVolume)) {
        fRemoveSafely = TRUE;

        if (PreventRemovalOfVolume(hVolume, FALSE) && AutoEjectVolume(hVolume))
            fAutoEject = TRUE;
    }

    if (!CloseHandle(hVolume))
        return FALSE;

    if (fAutoEject) {
        printf(
            "Media in Drive %c has been ejected safely.\n",
            cDriveLetter);
    }
    else {
        if (fRemoveSafely)
            printf(
                "Media in Drive %c can be safely removed.\n",
                cDriveLetter);
    }

    return TRUE;
}
