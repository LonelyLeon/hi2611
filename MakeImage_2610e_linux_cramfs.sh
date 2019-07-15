#!/bin/sh
##镜像制作脚本

##镜像大小
IMAGE_ALL_SIZE=0x4000000

##DDR驱动
# DDR2_800MHz_1Gb_PRINT.bin
# DDR3_1066MHz_1Gb_PRINT.bin
##
DDR_FILE=DDR3_PLL2_1333_16X1024_DEF_SSCG_OPEN_PRINT.bin

##原始loader镜像
LOADER_FILE=loader.bin

##海尔IC约定area2加载地址, loader入口-8
AREA2_EXEC_ADDR=0x81FFFFF8

##永新高安MarketId
MARCKET_ID=0xFFFFFFFF

##用户硬件配置文件
##CUSTOM_CONFIG_HW_FILE=HW_Config_NAND_CND_HDTV_IRLEHUA.bin		##HDV2611_PL
CUSTOM_CONFIG_HW_FILE=HW_Config_NAND_CND_TY_IRCNDRC6031.bin	##PAV2611

##用户软件配置文件
##CUSTOM_CONFIG_SW_FILE=SW_DEFAULT_IRHAIER_1366X768.bin
CUSTOM_CONFIG_SW_FILE=SW_Config_IRSIWEI_EN_800X480_RGB18_N.bin

##app在flash里的偏移地址
AREA3_OFFSET=0xa0000

##linux kernel文件夹位置
LINUX_KERNEL_DIR=/opt/fs

FSIMG_OFFSET=0x330000
FSIMG=cramfs.img

##app的os(hros/linux)
APP_OS=linux

##app压缩方式(lzss/gzip/none)
APP_COMPRESS_TYPE=gzip

##app压缩打包后的输出文件
APP_PACKED_FILE=app_packed.bin

##logo镜像
#LOGO_FILE=logo.bin

##logo在flash里的偏移地址
#LOGO_OFFSET=0x32c0000

##输出的完整镜像
IMAGE_FILE=image_all.bin

##大小端转换工具
#大端: echo
#小端: ./swap_u32)
##
SWAP="./swap_u32"

#############################################################################################
##  以下是执行命令
#############################################################################################
echo "Generate file '${IMAGE_FILE}'"

## 进入输出目录
cd ${OUTPUT_DIR}/bin

## 创建一个8M大小文件, 填充为0xFF
./MkFile -b 0xFF -s ${IMAGE_ALL_SIZE} -o ${IMAGE_FILE}

## 设置证书位置
./SetFileData -i ${IMAGE_FILE} -a 0x00 -d `${SWAP} 0xBE002000`

## 设置area2位置
./SetFileData -i ${IMAGE_FILE} -a 0x04 -d `${SWAP} 0xBE003000`

## 设置area1大小
DDR_SIZE=`wc -c ${DDR_FILE} | awk '{print int($1)}'`
##AREA1_SIZE=`expr ${DDR_SIZE} + 12`
AREA1_SIZE=6272
./SetFileData -i ${IMAGE_FILE} -a 0x08 -d `${SWAP} ${AREA1_SIZE}`

## 放置ddr驱动
echo "正在放置'${DDR_FILE}'"
./SetFileData -i ${IMAGE_FILE} -a 0x10 -f ${DDR_FILE}

## 放置证书

## 放置硬件配置数据(在签名后有(0x1000-512)字节的Gap)
if [ "x${CUSTOM_CONFIG_HW_FILE}" != x ]; then
	./SetFileData -i ${IMAGE_FILE} -a 0x2200 -f ${CUSTOM_CONFIG_HW_FILE}
fi

## 设置area2装载地址
./SetFileData -i ${IMAGE_FILE} -a 0x3000 -d `${SWAP} ${AREA2_EXEC_ADDR}`

## 设置area2大小(8+loader)
LOADER_SIZE=`wc -c ${LOADER_FILE} | awk '{print int($1)}'`

##判断loader大小是否可以放的下(LOADER_SIZE <= AREA3_OFFSET - 0x20000 - 0x3008)
LOADER_LIMIT_SIZE=$[${AREA3_OFFSET}-0x20000-0x3008]
if [ ${LOADER_SIZE} -gt ${LOADER_LIMIT_SIZE} ];then
	echo "Loader size '${LOADER_SIZE}' 超过了限制 '${LOADER_LIMIT_SIZE}'!";
	exit 1;
fi

AREA2_SIZE=`expr ${LOADER_SIZE} + 8`
./SetFileData -i ${IMAGE_FILE} -a 0x3004 -d `${SWAP} ${AREA2_SIZE}`

## 放置loader
./SetFileData -i ${IMAGE_FILE} -a 0x3008 -f ${LOADER_FILE}

## 放置MARCKET_ID
if [ "x${MARCKET_ID}" != x ]; then
	./SetFileData -i ${IMAGE_FILE} -a 0x3010 -d `${SWAP} ${MARCKET_ID}`
fi

## 压缩并打包app
config=${LINUX_KERNEL_DIR}/Platform
addr=$(fgrep load-\$\(CONFIG_MIPS_HI2610E\) $config | sed 's/.*0xffffffff\(.*\)$/\1/')
kernel_entry=$(grep kernel_entry ${LINUX_KERNEL_DIR}/System.map | cut -d ' ' -f 1)

cp -av ${LINUX_KERNEL_DIR}/vmlinux.bin vmlinux.bin
cp -av ${LINUX_KERNEL_DIR}/${FSIMG} ./

rm -rf vmlinux.img

TEMP_FILE=app_temp_xxxx_file
cp -a vmlinux.bin ${TEMP_FILE}
gzip ${TEMP_FILE}
mv ${TEMP_FILE}.gz ${TEMP_FILE}

echo "generating vmlinux.img"
./mkimage -A mips -O linux -T kernel -C gzip -a $addr -e $kernel_entry -d ${TEMP_FILE} -r ${CUSTOM_CONFIG_SW_FILE} vmlinux.img
rm -rf ${TEMP_FILE}

cp -a vmlinux.img ${APP_PACKED_FILE}
./SetFileData -i ${IMAGE_FILE} -a ${AREA3_OFFSET} -f ${APP_PACKED_FILE}

./SetFileData -i ${IMAGE_FILE} -a ${FSIMG_OFFSET} -f ${FSIMG}

if [ "x${LOGO_FILE}" != x ]; then
	./SetFileData -i ${IMAGE_FILE} -a ${LOGO_OFFSET} -f ${LOGO_FILE}
fi

BOOTLOADER_SIZE=524288
##dd if=${IMAGE_FILE} of=bootloader.bin bs=1 count=${BOOTLOADER_SIZE}
./GetFileData -i ${IMAGE_FILE} -a 0 -l ${BOOTLOADER_SIZE} -o bootloader.bin
./GetFileData -i ${IMAGE_FILE} -a 0xa0000 -l 0x3F00000 -o lessbootloader.bin

## 退回到原来目录
cd ${WORKROOT}

#############################################################################################
#############################################################################################
echo "End!"
## end
