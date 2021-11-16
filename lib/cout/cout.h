#pragma once

struct my_stream_tag{};

template<typename T> my_stream_tag const& operator<<(my_stream_tag const& os, T const& t){
      Serial.print(t);
      return os;
}

static constexpr my_stream_tag cout;

static constexpr auto endl = '\n';

