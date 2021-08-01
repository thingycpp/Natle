#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "TL.hpp"

namespace tl {

	// Natle's GUI, of course updated as it went along
	class NatleGUI {

	public:

		static void initUI(GLFWwindow* p_window);

		static void UI();

		static bool showEntSettings;
		static bool showDesc;
		static ImVec4 clear_color;

		static float fontSize;

		static const char* NatleDesc;

	private:
		NatleGUI() {}
		~NatleGUI() {}

	};

}

#endif