TTF_Font* font;

SDL_Rect solidRect;
SDL_Rect blendedRect;
SDL_Rect shadedRect;

bool SetupTTF( const std::string &fontName );
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
void CreateTextTextures();
void Init();

// Path for a TrueType font in ubuntu 16.04
std::string = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";

int main()
{
	Init();
	renderer = SDL_CreateRenderer(window, -1, 0);
	SetupRenderer();
	SetupTTF( "/usr/share/fonts/truetype/freefont/FreeSans.ttf" );
	CreateTextTextures();
        SDL_RenderCopy( renderer, solidTexture, nullptr, &solidRect );
        SDL_RenderCopy( renderer, blendedTexture, nullptr, &blendedRect );
	SDL_RenderCopy( renderer, shadedTexture, nullptr, &shadedRect );
}

void Init()
{
	// Initiliaze SDL video and our timer //
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0 )
	{
        std::cout << "Unable to initialize SDL2: " << SDL_GetError() << std::endl;
	};
	window = SDL_CreateWindow(WINDOW_CAPTION,SDL_WINDOWPOS_UNDEFINED, 
				  SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
	// Adding some graphics for the icon of the application
	SDL_Surface* surface2 = IMG_Load( "./atari.png" );
	// The icon is attached to the window pointer
    	SDL_SetWindowIcon(window, surface2);
	SDL_FreeSurface(surface2);
}

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
