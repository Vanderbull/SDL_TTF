bool SetupTTF( const std::string &fontName)
{
	// SDL2_TTF needs to be initialized just like SDL2
	if ( TTF_Init() == -1 )
	{
		std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
		return false;
	}

	// Load our fonts, with a huge size
	font = TTF_OpenFont( fontName.c_str(), 90 );

	// Error check
	if ( font == nullptr )
	{
		std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
