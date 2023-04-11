#ifndef AUDIO_HPP
#define AUDIO_HPP

struct Audio 
{
    constexpr Audio() = default;
    ~Audio();
    Audio(const Audio&) = delete;
    Audio(Audio&&) = default;
    Audio& operator=(const Audio&) = delete;
    Audio& operator=(Audio&&) = default;
};

#endif // AUDIO_HPP