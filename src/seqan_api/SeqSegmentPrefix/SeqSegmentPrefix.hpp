// vim: set noexpandtab tabstop=2:

#pragma once

class SeqSegmentPrefix
{
  public:
    SeqSegmentPrefix(const void *);
    ~SeqSegmentPrefix();
  private:
    void * impl_; 
};
