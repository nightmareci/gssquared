#include "gs2.hpp"
#include "TextRenderer.hpp"

/**
 * @brief Constructor for the TextRenderer class
 * 
 * @param renderer The SDL renderer to use
 * @param font_path The path to the requested font to use
 * @param font_size The size of the requested font to use
 * 
 * If the font is not found, the debug font will be used.
 */

TextRenderer::TextRenderer(SDL_Renderer *renderer, const std::string &font_path, float font_size) {
    this->renderer = renderer;
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialise SDL_ttf: %s\n", SDL_GetError());
    }

    /* load up the font */
    use_debug_font = false;
    font_size = 15.0f;
    std::string font_path_full = gs2_app_values.base_path + font_path;
    font = TTF_OpenFont(font_path_full.c_str(), font_size);
    if (!font) {
        use_debug_font = true;
        font_line_height = 14;
        printf("Failed to load TTF font %s\n", font_path_full.c_str());
    } else {
        font_line_height = TTF_GetFontHeight(font);
        engine = TTF_CreateRendererTextEngine(renderer);
    }
}

TextRenderer::~TextRenderer() {
    TTF_DestroyRendererTextEngine(engine);
    TTF_CloseFont(font);
    TTF_Quit();
}

/** 
 * seems like maybe I should create a texture once, based on the window size.
 * Lock, draw text to it, unlock, like we do the video code, then render that? rather than doing so many individual gpu calls.
 * I can also add a "dirty" flag so if the screen hasn't changed, we don't need to render everything. tho, unchanged lines here are
 * rare.
 */

void TextRenderer::render(const std::string &text, int x, int y) {
    if (use_debug_font) {
        SDL_RenderDebugText(renderer, x, y, text.c_str());
    } else {
        TTF_Text *ttf_text = TTF_CreateText(engine, font, text.c_str(), 0);
        TTF_DrawRendererText(ttf_text, (float)x, (float)y);
        TTF_DestroyText(ttf_text);

    }
}
