#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message {
public:
  enum { hdr_len = 4 };
  enum { max_body_len = 512 };

  chat_message() : body_len(0) { }

  const char* data() const { return data_; }

  char* data() { return data_; }

  size_t length() const { return hdr_len + body_len; }

  const char* body() const { return data_ + hdr_len;}

  char* body() { return data_ + hdr_len; }

  size_t body_length() const { return body_len; }

  void body_length(size_t new_length) {
    body_len = new_length;
    if (body_len > max_body_len)
      body_len = max_body_len;
  }

  bool decode_header() {
    char header[hdr_len + 1] = "";
    std::strncat(header, data_, hdr_len);
    body_len = std::atoi(header);
    if (body_len > max_body_len) {
      body_len = 0;
      return false;
    }
    return true;
  }

  void encode_header() {
    char header[hdr_len + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(body_len));
    std::memcpy(data_, header, hdr_len);
  }

private:
  char data_[hdr_len + max_body_len];
  size_t body_len;
};

#endif // CHAT_MESSAGE_HPP
