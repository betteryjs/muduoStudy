#include "TlsStream.h"

TlsStreamPtr TlsStream::connect(TlsConfig* config, const char* hostport, const char* servername)
{
  TlsStreamPtr stream;
  TlsContext context(TlsContext::kClient, config);
  if (context.connect(hostport, servername))
  {
    LOG_ERROR << context.error();
    return stream;
  }
  if (context.handshake())
  {
    LOG_ERROR << context.error();
    return stream;
  }
  stream.reset(new TlsStream(std::move(context)));
  return stream;
}

int TlsStream::receiveSome(void* buf, int len)
{
  return context_.read(buf, len);
}

int TlsStream::sendSome(const void* buf, int len)
{
  return context_.write(buf, len);
}
