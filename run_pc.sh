
if [ "$1" = "d" ]; then
	F:/WINDDK/7600.16385.1/Debuggers/windbg $OUTPUT_DIR/bin/app.exe
else
	$OUTPUT_DIR/bin/app.exe
fi
