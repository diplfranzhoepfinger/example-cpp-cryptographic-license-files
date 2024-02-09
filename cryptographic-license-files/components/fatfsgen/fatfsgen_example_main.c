/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_system.h"
#include "sdkconfig.h"


#define EXAMPLE_FATFS_MODE_READ_ONLY false

#if CONFIG_FATFS_LFN_NONE
#define EXAMPLE_FATFS_LONG_NAMES false
#else
#define EXAMPLE_FATFS_LONG_NAMES true
#endif

static const char *TAG = "example";


// Mount path for the partition
const char *base_path = "/spiflash";

// Handle of the wear levelling library instance
static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;

void fatfsgen_example_mount(void)
{
    ESP_LOGI(TAG, "Mounting FAT filesystem");
    // To mount device we need name of device partition, define base_path
    // and allow format partition in case if it is new one and was not formatted before
    const esp_vfs_fat_mount_config_t mount_config = {
            .max_files = 4,
            .format_if_mount_failed = false,
            .allocation_unit_size = CONFIG_WL_SECTOR_SIZE
    };
    esp_err_t err;
    if (EXAMPLE_FATFS_MODE_READ_ONLY){
        err = esp_vfs_fat_spiflash_mount_ro(base_path, "storage", &mount_config);
    } else {
        err = esp_vfs_fat_spiflash_mount_rw_wl(base_path, "storage", &mount_config, &s_wl_handle);
    }

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount FATFS (%s)", esp_err_to_name(err));
        return;
    }

}

void fatfsgen_example_unmount(void)
{
    // Unmount FATFS
    ESP_LOGI(TAG, "Unmounting FAT filesystem");
    if (EXAMPLE_FATFS_MODE_READ_ONLY){
        ESP_ERROR_CHECK(esp_vfs_fat_spiflash_unmount_ro(base_path, "storage"));
    } else {
        ESP_ERROR_CHECK(esp_vfs_fat_spiflash_unmount_rw_wl(base_path, s_wl_handle));
    }
    ESP_LOGI(TAG, "Done");
}
