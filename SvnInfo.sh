## 进入输出目录
cd $WORKROOT/project/$PROJECT/include
		svn info | grep -a Revision | awk '{ printf("#ifndef _D_REVISION_H_\n#define _D_REVISION_H_\n\n#ifdef  __cplusplus\nextern \"C\"\n{\n#endif\n#define REVISION \"%s\"\n \n#ifdef  __cplusplus\n}\n#endif\n#endif\n", $$0) }' > ver.h; 
## 退回到原来目录
cd ${WORKROOT}
