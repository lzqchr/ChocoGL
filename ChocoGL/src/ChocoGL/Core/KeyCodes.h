#pragma once

namespace ChocoGL
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define CL_KEY_SPACE           ::ChocoGL::Key::Space
#define CL_KEY_APOSTROPHE      ::ChocoGL::Key::Apostrophe    /* ' */
#define CL_KEY_COMMA           ::ChocoGL::Key::Comma         /* , */
#define CL_KEY_MINUS           ::ChocoGL::Key::Minus         /* - */
#define CL_KEY_PERIOD          ::ChocoGL::Key::Period        /* . */
#define CL_KEY_SLASH           ::ChocoGL::Key::Slash         /* / */
#define CL_KEY_0               ::ChocoGL::Key::D0
#define CL_KEY_1               ::ChocoGL::Key::D1
#define CL_KEY_2               ::ChocoGL::Key::D2
#define CL_KEY_3               ::ChocoGL::Key::D3
#define CL_KEY_4               ::ChocoGL::Key::D4
#define CL_KEY_5               ::ChocoGL::Key::D5
#define CL_KEY_6               ::ChocoGL::Key::D6
#define CL_KEY_7               ::ChocoGL::Key::D7
#define CL_KEY_8               ::ChocoGL::Key::D8
#define CL_KEY_9               ::ChocoGL::Key::D9
#define CL_KEY_SEMICOLON       ::ChocoGL::Key::Semicolon     /* ; */
#define CL_KEY_EQUAL           ::ChocoGL::Key::Equal         /* = */
#define CL_KEY_A               ::ChocoGL::Key::A
#define CL_KEY_B               ::ChocoGL::Key::B
#define CL_KEY_C               ::ChocoGL::Key::C
#define CL_KEY_D               ::ChocoGL::Key::D
#define CL_KEY_E               ::ChocoGL::Key::E
#define CL_KEY_F               ::ChocoGL::Key::F
#define CL_KEY_G               ::ChocoGL::Key::G
#define CL_KEY_H               ::ChocoGL::Key::H
#define CL_KEY_I               ::ChocoGL::Key::I
#define CL_KEY_J               ::ChocoGL::Key::J
#define CL_KEY_K               ::ChocoGL::Key::K
#define CL_KEY_L               ::ChocoGL::Key::L
#define CL_KEY_M               ::ChocoGL::Key::M
#define CL_KEY_N               ::ChocoGL::Key::N
#define CL_KEY_O               ::ChocoGL::Key::O
#define CL_KEY_P               ::ChocoGL::Key::P
#define CL_KEY_Q               ::ChocoGL::Key::Q
#define CL_KEY_R               ::ChocoGL::Key::R
#define CL_KEY_S               ::ChocoGL::Key::S
#define CL_KEY_T               ::ChocoGL::Key::T
#define CL_KEY_U               ::ChocoGL::Key::U
#define CL_KEY_V               ::ChocoGL::Key::V
#define CL_KEY_W               ::ChocoGL::Key::W
#define CL_KEY_X               ::ChocoGL::Key::X
#define CL_KEY_Y               ::ChocoGL::Key::Y
#define CL_KEY_Z               ::ChocoGL::Key::Z
#define CL_KEY_LEFT_BRACKET    ::ChocoGL::Key::LeftBracket   /* [ */
#define CL_KEY_BACKSLASH       ::ChocoGL::Key::Backslash     /* \ */
#define CL_KEY_RIGHT_BRACKET   ::ChocoGL::Key::RightBracket  /* ] */
#define CL_KEY_GRAVE_ACCENT    ::ChocoGL::Key::GraveAccent   /* ` */
#define CL_KEY_WORLD_1         ::ChocoGL::Key::World1        /* non-US #1 */
#define CL_KEY_WORLD_2         ::ChocoGL::Key::World2        /* non-US #2 */

/* Function keys */
#define CL_KEY_ESCAPE          ::ChocoGL::Key::Escape
#define CL_KEY_ENTER           ::ChocoGL::Key::Enter
#define CL_KEY_TAB             ::ChocoGL::Key::Tab
#define CL_KEY_BACKSPACE       ::ChocoGL::Key::Backspace
#define CL_KEY_INSERT          ::ChocoGL::Key::Insert
#define CL_KEY_DELETE          ::ChocoGL::Key::Delete
#define CL_KEY_RIGHT           ::ChocoGL::Key::Right
#define CL_KEY_LEFT            ::ChocoGL::Key::Left
#define CL_KEY_DOWN            ::ChocoGL::Key::Down
#define CL_KEY_UP              ::ChocoGL::Key::Up
#define CL_KEY_PAGE_UP         ::ChocoGL::Key::PageUp
#define CL_KEY_PAGE_DOWN       ::ChocoGL::Key::PageDown
#define CL_KEY_HOME            ::ChocoGL::Key::Home
#define CL_KEY_END             ::ChocoGL::Key::End
#define CL_KEY_CAPS_LOCK       ::ChocoGL::Key::CapsLock
#define CL_KEY_SCROLL_LOCK     ::ChocoGL::Key::ScrollLock
#define CL_KEY_NUM_LOCK        ::ChocoGL::Key::NumLock
#define CL_KEY_PRINT_SCREEN    ::ChocoGL::Key::PrintScreen
#define CL_KEY_PAUSE           ::ChocoGL::Key::Pause
#define CL_KEY_F1              ::ChocoGL::Key::F1
#define CL_KEY_F2              ::ChocoGL::Key::F2
#define CL_KEY_F3              ::ChocoGL::Key::F3
#define CL_KEY_F4              ::ChocoGL::Key::F4
#define CL_KEY_F5              ::ChocoGL::Key::F5
#define CL_KEY_F6              ::ChocoGL::Key::F6
#define CL_KEY_F7              ::ChocoGL::Key::F7
#define CL_KEY_F8              ::ChocoGL::Key::F8
#define CL_KEY_F9              ::ChocoGL::Key::F9
#define CL_KEY_F10             ::ChocoGL::Key::F10
#define CL_KEY_F11             ::ChocoGL::Key::F11
#define CL_KEY_F12             ::ChocoGL::Key::F12
#define CL_KEY_F13             ::ChocoGL::Key::F13
#define CL_KEY_F14             ::ChocoGL::Key::F14
#define CL_KEY_F15             ::ChocoGL::Key::F15
#define CL_KEY_F16             ::ChocoGL::Key::F16
#define CL_KEY_F17             ::ChocoGL::Key::F17
#define CL_KEY_F18             ::ChocoGL::Key::F18
#define CL_KEY_F19             ::ChocoGL::Key::F19
#define CL_KEY_F20             ::ChocoGL::Key::F20
#define CL_KEY_F21             ::ChocoGL::Key::F21
#define CL_KEY_F22             ::ChocoGL::Key::F22
#define CL_KEY_F23             ::ChocoGL::Key::F23
#define CL_KEY_F24             ::ChocoGL::Key::F24
#define CL_KEY_F25             ::ChocoGL::Key::F25

/* Keypad */
#define CL_KEY_KP_0            ::ChocoGL::Key::KP0
#define CL_KEY_KP_1            ::ChocoGL::Key::KP1
#define CL_KEY_KP_2            ::ChocoGL::Key::KP2
#define CL_KEY_KP_3            ::ChocoGL::Key::KP3
#define CL_KEY_KP_4            ::ChocoGL::Key::KP4
#define CL_KEY_KP_5            ::ChocoGL::Key::KP5
#define CL_KEY_KP_6            ::ChocoGL::Key::KP6
#define CL_KEY_KP_7            ::ChocoGL::Key::KP7
#define CL_KEY_KP_8            ::ChocoGL::Key::KP8
#define CL_KEY_KP_9            ::ChocoGL::Key::KP9
#define CL_KEY_KP_DECIMAL      ::ChocoGL::Key::KPDecimal
#define CL_KEY_KP_DIVIDE       ::ChocoGL::Key::KPDivide
#define CL_KEY_KP_MULTIPLY     ::ChocoGL::Key::KPMultiply
#define CL_KEY_KP_SUBTRACT     ::ChocoGL::Key::KPSubtract
#define CL_KEY_KP_ADD          ::ChocoGL::Key::KPAdd
#define CL_KEY_KP_ENTER        ::ChocoGL::Key::KPEnter
#define CL_KEY_KP_EQUAL        ::ChocoGL::Key::KPEqual

#define CL_KEY_LEFT_SHIFT      ::ChocoGL::Key::LeftShift
#define CL_KEY_LEFT_CONTROL    ::ChocoGL::Key::LeftControl
#define CL_KEY_LEFT_ALT        ::ChocoGL::Key::LeftAlt
#define CL_KEY_LEFT_SUPER      ::ChocoGL::Key::LeftSuper
#define CL_KEY_RIGHT_SHIFT     ::ChocoGL::Key::RightShift
#define CL_KEY_RIGHT_CONTROL   ::ChocoGL::Key::RightControl
#define CL_KEY_RIGHT_ALT       ::ChocoGL::Key::RightAlt
#define CL_KEY_RIGHT_SUPER     ::ChocoGL::Key::RightSuper
#define CL_KEY_MENU            ::ChocoGL::Key::Menu

// Mouse (TODO: move into separate file probably)
#define CL_MOUSE_BUTTON_LEFT    0
#define CL_MOUSE_BUTTON_RIGHT   1
#define CL_MOUSE_BUTTON_MIDDLE  2