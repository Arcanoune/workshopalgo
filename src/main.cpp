#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <math.h>
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>

void keep_green_only(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

void channels_swap(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void blackandwhite(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        float luminance = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
        color.r = luminance;
        color.g = luminance;
        color.b = luminance;
    }
}

void negatif(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (glm::vec3 &color : image.pixels())
    {
        color = 1.f - color;
    }
}

void gradende() // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image image{300 /*width*/, 200 /*height*/};

    for (int x{0}; x < image.width(); x++)
    {
        float taille_actuelle = static_cast<float>(x);
        float taille_totale = static_cast<float>(image.width());
        float pourcentage{taille_actuelle / taille_totale};

        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = pourcentage;
            image.pixel(x, y).g = pourcentage;
            image.pixel(x, y).b = pourcentage;
        }
    }
    image.save("output/gradende.png");
}

void miroir(sil::Image &image)
{
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width() / 2; x++)
        {
            // Inverser directement les canaux de couleur
            std::swap(image.pixel(x, y).r, image.pixel(image.width() - 1 - x, y).r);
            std::swap(image.pixel(x, y).g, image.pixel(image.width() - 1 - x, y).g);
            std::swap(image.pixel(x, y).b, image.pixel(image.width() - 1 - x, y).b);
        }
    }
}

void bruit(sil::Image &image)
{

    for (int x{0}; x < image.width(); x++)
    {
        float taille_actuelle = static_cast<float>(x);
        float taille_totale = static_cast<float>(image.width());
        float pourcentage{taille_actuelle / taille_totale};

        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(random_float(0, image.width()), random_float(0, image.height())).r = pourcentage;
            image.pixel(random_float(0, image.width()), random_float(0, image.height())).g = pourcentage;
            image.pixel(random_float(0, image.width()), random_float(0, image.height())).b = pourcentage;
        }
    }
}

void angledroit(sil::Image &image)
{
    int new_width = image.height();
    int new_height = image.width();
    sil::Image new_image{new_width, new_height};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }
    image = new_image;
}

void rgbsplit(sil::Image &image)
{
    sil::Image original = image;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int xred = std::max(0, x - 10);
            int xblue = std::min(image.width() - 1, x + 10);

            image.pixel(x, y).r = original.pixel(xred, y).r;
            image.pixel(x, y).g = original.pixel(x, y).g;
            image.pixel(x, y).b = original.pixel(xblue, y).b;
        }
    }
}

void luminosite(sil::Image &image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            image.pixel(x, y).r = pow(image.pixel(x, y).r, 2);
            image.pixel(x, y).g = pow(image.pixel(x, y).g, 2);
            image.pixel(x, y).b = pow(image.pixel(x, y).b, 2);
        }
    }
}

void disque() // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image image{500 /*width*/, 500 /*height*/};

    float x0 = image.width() / 2;
    float y0 = image.height() / 2;
    float radius = 125;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (pow(x - x0, 2) + pow(y - y0, 2) <= pow(radius, 2))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
    image.save("output/disque.png");
}

void cercle(sil::Image &image) // Modification : Prend une image en paramètre
{
    float x0 = image.width() / 2;
    float y0 = image.height() / 2;
    float radius = 100;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (pow(x - x0, 2) + pow(y - y0, 2) <= pow(radius, 2) && pow(x - x0, 2) + pow(y - y0, 2) >= pow(radius, 1.95))
            {
                image.pixel(x, y) = {1, 1, 1};
            }
        }
    }
}

void animation() // Prend l'image par référence pour pouvoir la modifier
{
    sil::Image image{500 /*width*/, 500 /*height*/};

    for (float incre = 0; incre < 10; incre++)
    {
        float x0 = image.width() / 2;
        float y0 = image.height() / 2;
        float radius = 125;

        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                if (pow(x - x0, 2) + pow(y - y0, 2) <= pow(radius, pow(incre, 0.2)))
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
        int nb = static_cast<float>(incre);
        image.save("output/animation" + std::to_string(nb) + ".png");
    }
}

void rosace()
{
    sil::Image image{500 /*width*/, 500 /*height*/};
    float x0 = image.width() / 2;
    float y0 = image.height() / 2;
    float radius = 100;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (pow(x - x0, 2) + pow(y - y0, 2) <= pow(radius, 2) && pow(x - x0, 2) + pow(y - y0, 2) >= pow(radius, 1.95))
            {
                image.pixel(x, y) = {1, 1, 1};
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        float xi = x0 + radius * cos(i * (M_PI / 3));
        float yi = y0 + radius * sin(i * (M_PI / 3));

        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                if (pow(x - xi, 2) + pow(y - yi, 2) <= pow(radius, 2) && pow(x - xi, 2) + pow(y - yi, 2) >= pow(radius, 1.95))
                {
                    image.pixel(x, y) = {1, 1, 1};
                }
            }
        }
    }
    image.save("output/rosace.png");
}

void mosaique(sil::Image &image)
{
    int width = image.width();
    int height = image.height();
    int final_width = width * 4;
    int final_height = height * 4;

    sil::Image img{final_width, final_height};

    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            int src_x = x % width;
            int src_y = y % height;

            img.pixel(x, y) = image.pixel(src_x, src_y);
        }
    }
    image = img;
}

void mosaiquemiroir(sil::Image &image)
{
    int width = image.width();
    int height = image.height();
    int final_width = width * 4;
    int final_height = height * 4;

    sil::Image img{final_width, final_height};

    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            int pos_x = x / width;
            int pos_y = y / height;

            int src_x = x % width;
            int src_y = y % height;

            if ((pos_x + pos_y) % 2 == 0)
            {
                src_x = width - 1 - src_x;
            }

            img.pixel(x, y) = image.pixel(src_x, src_y);
        }
    }
    image = img;
}

void glitch(sil::Image &image)
{
    int width = image.width() / 10;
    int height = image.height() / 50;

    for (int i = 0; i < 30; i++)
    {
        int x1 = random_int(0, image.width() - width);
        int y1 = random_int(0, image.height() - height);

        int x2 = random_int(0, image.width() - width);
        int y2 = random_int(0, image.height() - height);

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if (x1 + x < image.width() && y1 + y < image.height() &&
                    x2 + x < image.width() && y2 + y < image.height())
                {
                    auto temp = image.pixel(x1 + x, y1 + y);
                    image.pixel(x1 + x, y1 + y) = image.pixel(x2 + x, y2 + y);
                    image.pixel(x2 + x, y2 + y) = temp;
                }
            }
        }
    }
}

// tri de pixels
// dégradés couleur

void fractale()
{
    sil::Image image{500 /*width*/, 500 /*height*/};

    int max_iterations = 20; // Nombre d'itérations pour déterminer la divergence
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            // Mappage des coordonnées (x, y) dans l'espace complexe
            std::complex<float> c{
                (x - image.width() / 2.0f) * 4.0f / image.width(),
                (y - image.height() / 2.0f) * 4.0f / image.height()};

            std::complex<float> z{0.f};
            float iterations = 0;

            // Algorithme de Mandelbrot
            while (iterations < max_iterations && std::abs(z) <= 2.0f)
            {
                z = z * z + c;
                iterations++;
            }

            image.pixel(x, y) = {iterations / max_iterations, iterations / max_iterations, iterations / max_iterations};
        }
    }
    image.save("output/fractale.png");
}

// tramage
// normalisation histrogramme

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}
void vortex(sil::Image &image)
{
    float x0 = image.width() / 2.0f;
    float y0 = image.height() / 2.0f;
    float angleswish = 0.05f;

    glm::vec2 center_of_rotation{x0, y0};
    sil::Image img = image; 

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            glm::vec2 point{x, y};
            float distance = glm::distance(point, center_of_rotation);
            float angle = distance * angleswish;

            glm::vec2 rotate = rotated(point, center_of_rotation, angle);

            int X = rotate.x;
            int Y = rotate.y;

            if (X >= 0 && X < image.width() && Y >= 0 && Y < image.height())
            {
                image.pixel(x, y) = img.pixel(X, Y); 
            }
        }
    }
}



int main()
{
    // {
    //     sil::Image image{"images/logo.png"};      // Lis l'image
    //     keep_green_only(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/keep_green_only.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};    // Lis l'image
    //     channels_swap(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/channels_swap.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};    // Lis l'image
    //     blackandwhite(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/blackandwhite.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     negatif(image);                      // Utilise la fonction pour modifier l'image
    //     image.save("output/negatif.png");    // Sauvegarde l'image
    // }
    // {
    //     gradende(); // Utilise la fonction pour modifier l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     miroir(image);                       // Utilise la fonction pour modifier l'image
    //     image.save("output/miroir.png");     // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     bruit(image);                        // Utilise la fonction pour modifier l'image
    //     image.save("output/bruit.png");      // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     angledroit(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/angledroit.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     luminosite(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/luminosite.png"); // Sauvegarde l'image
    // }
    // {
    //     disque(); // Utilise la fonction pour modifier l'image
    // }
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     cercle(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/cercle.png"); // Sauvegarde l'image
    // }
    // {
    //     animation(); // Utilise la fonction pour modifier l'image
    // }
    {
        rosace(); // Utilise la fonction pour modifier l'image
    }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/mosaique.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaiquemiroir(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/mosaiquemiroir.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     glitch(image);                   // Utilise la fonction pour modifier l'image
    //     image.save("output/glitch.png"); // Sauvegarde l'image
    // }
    // {
    //     fractale();
    // }
    {
        sil::Image image{"images/logo.png"};
        vortex(image);                   // Utilise la fonction pour modifier l'image
        image.save("output/vortex.png"); // Sauvegarde l'image
    }
}
