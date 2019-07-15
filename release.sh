#!/bin/bash
ARCH_TYPE=hi2610e
DEST_DIR=/home/nfsroot/${ARCH_TYPE}
mkdir -p ${DEST_DIR}
cp -av output/bin/app.elf ${DEST_DIR}
chmod 777 ${DEST_DIR}/app.elf
cp -av output/modules/*.ko ${DEST_DIR}

echo "Generate run.sh..."
RUN_SH=${DEST_DIR}/../run.sh
echo "#!/bin/sh" > ${RUN_SH}
echo "tftp -g -l app.elf -r ${ARCH_TYPE}/app.elf \${SERVER};chmod 777 app.elf" >> ${RUN_SH}
for i in `ls ${DEST_DIR}/*.ko`;do
ko=`basename $i`;
echo "tftp -g -l ${ko} -r ${ARCH_TYPE}/${ko} \${SERVER}" >> ${RUN_SH};
done

DEST_DIR=/home/nfsroot/${ARCH_TYPE}
mkdir -p ${DEST_DIR}
cp -av output/bin/app.elf ${DEST_DIR}
chmod 777 ${DEST_DIR}/app.elf
cp -av output/modules/*.ko ${DEST_DIR}


echo "OK!"

