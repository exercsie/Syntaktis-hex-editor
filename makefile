IMGUI = Dependencies/imgui
CPPCODEC = Dependencies/cppcodec

GUI_FLAGS = -I${IMGUI} -I${IMGUI}/backends -I${CPPCODEC}

MYGUI_FILES = \
	src/Main.cpp \
	src/Gui.cpp \
	src/ByteLogic.cpp \
	src/File.cpp \
	src/FileEditorView.cpp

IMGUI_FILES = \
	$(IMGUI)/imgui.cpp \
	$(IMGUI)/imgui_draw.cpp \
	$(IMGUI)/imgui_tables.cpp \
	$(IMGUI)/imgui_widgets.cpp \
	$(IMGUI)/backends/imgui_impl_glfw.cpp \
	$(IMGUI)/backends/imgui_impl_opengl3.cpp \
	${IMGUI}/misc/cpp/imgui_stdlib.cpp

GUI_SUFFIX_FLAGS = -lglfw -lGL -ldl -std=c++23

SyntaktisHexEditor:
	g++ ${GUI_FLAGS} ${MYGUI_FILES} ${IMGUI_FILES} -o Build/SyntaktisHexEditor ${GUI_SUFFIX_FLAGS}

clean:
	rm -f Build/SyntaktisHexEditor