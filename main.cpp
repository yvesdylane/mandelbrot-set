#include <SDL2/SDL.h>
#include <numeric>
#include <complex>

double lerp(double a, double b, double t) {
  return (1.0 - t) * a + t * b;
}

int is_in_set(std::complex<double> c)
{
    std::complex<double>z(0,0);
    for(int i = 0; i < 250; i++)
    {
        z = std::pow(z, 2) + c;
        if(std::norm(z) > 10)
        {
            return i;
        }
    }
    return 0;
}

int main( int argc, char * argv[] )
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(1000, 800, 0, &window, &renderer);

    for(double x = 0.0; x < 1.0; x += 0.001)
        for(double y = 0.0; y < 1.0; y += 0.001)
        {
           double point_x = lerp(-2.0, 2.0, x);
           double point_y = lerp(-2.0, 2.0, y);
           int iters = is_in_set(std::complex<double>(point_x, point_y));
           if(iters == 0)
           {
               SDL_SetRenderDrawColor(renderer, 35, 13, 14, 255);
               SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
           }
           else{
               SDL_SetRenderDrawColor(renderer,
                                      15 * iters % 250,
                                      13 * iters % 250,
                                      14 * iters % 250,
                                      255);
               SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
           }
        }

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    return 0;
}
