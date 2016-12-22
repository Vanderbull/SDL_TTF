TTF_Font* font;

SDL_Rect solidRect;
SDL_Rect blendedRect;
SDL_Rect shadedRect;

bool SetupTTF( const std::string &fontName );
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
void CreateTextTextures();

// Path for a TrueType font in ubuntu 16.04
std::string = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";

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

void CreateTextTextures()
{
    	high_resolution_clock::time_point t1 = high_resolution_clock::now();
    	SDL_Delay(100);
    	high_resolution_clock::time_point t2 = high_resolution_clock::now();

    	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    	std::cout << "It took me " << time_span.count() << " seconds.";
    	std::cout << std::endl;

    	std::string f_str = std::to_string(time_span.count());
	SDL_Surface* solid = TTF_RenderText_Solid( font, f_str.c_str(), textColor );
	solidTexture = SurfaceToTexture( solid );

	SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
	solidRect.x = 0;
	solidRect.y = 0;

	SDL_Surface* blended = TTF_RenderText_Blended( font, "blended", textColor );
	blendedTexture = SurfaceToTexture( blended );

	SDL_QueryTexture( blendedTexture, NULL, NULL, &blendedRect.w, &blendedRect.h );
	blendedRect.x = 0;
	blendedRect.y = solidRect.y + solidRect.h +  20;

	SDL_Surface* shaded = TTF_RenderText_Shaded( font, "shaded", textColor, backgroundColor );
	shadedTexture = SurfaceToTexture( shaded );

	SDL_QueryTexture( shadedTexture , NULL, NULL, &shadedRect.w, &shadedRect.h );
	shadedRect.x = 0;
	shadedRect.y = blendedRect.y + blendedRect.h + 20;
}

// Convert an SDL_Surface to SDL_Texture.
SDL_Texture* SurfaceToTexture( SDL_Surface* surf )
{
	SDL_Texture* text;
	text = SDL_CreateTextureFromSurface( renderer, surf );
	SDL_FreeSurface( surf );
	return text;
}
