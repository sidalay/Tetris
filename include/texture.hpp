#ifndef TEXTURE_HPP
#define TEXTURE_HPP

struct Texture {

    constexpr Texture() = default;
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = default;
};

#endif // TEXTURE_HPP