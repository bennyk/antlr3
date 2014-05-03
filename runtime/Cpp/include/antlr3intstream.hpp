#ifndef	_ANTLR3_INTSTREAM_HPP
#define	_ANTLR3_INTSTREAM_HPP

ANTLR_BEGIN_NAMESPACE()

template<class ImplTraits>
class IntStream : public ImplTraits::AllocPolicyType
{
public:
    /** Consume the next 'ANTR3_UINT32' in the stream
     */
    virtual void		    consume() = 0;
    
    /** Get ANTLR3_UINT32 at current input pointer + i ahead where i=1 is next ANTLR3_UINT32
     */
    virtual ANTLR_UINT32	_LA( ANTLR_INT32 i) = 0;
    
    /** Tell the stream to start buffering if it hasn't already.  Return
     *  current input position, index(), or some other marker so that
     *  when passed to rewind() you get back to the same spot.
     *  rewind(mark()) should not affect the input cursor.
     */
    virtual ANTLR_MARKER	    mark() = 0;
    
    /** Return the current input symbol index 0..n where n indicates the
     *  last symbol has been read.
     */
    virtual ANTLR_MARKER	    index() = 0;
    
    /** Reset the stream so that next call to index would return marker.
     *  The marker will usually be index() but it doesn't have to be.  It's
     *  just a marker to indicate what state the stream was in.  This is
     *  essentially calling release() and seek().  If there are markers
     *  created after this marker argument, this routine must unroll them
     *  like a stack.  Assume the state the stream was in when this marker
     *  was created.
     */
    virtual void	rewind(ANTLR_MARKER marker) = 0;
    
    /** Reset the stream to the last marker position, witouh destryoing the
     *  last marker position.
     */
    virtual void	rewindLast() = 0;
    
    /** You may want to commit to a backtrack but don't want to force the
     *  stream to keep bookkeeping objects around for a marker that is
     *  no longer necessary.  This will have the same behavior as
     *  rewind() except it releases resources without the backward seek.
     */
    virtual void	release(ANTLR_MARKER mark) = 0;
    
    /** Set the input cursor to the position indicated by index.  This is
     *  normally used to seek ahead in the input stream.  No buffering is
     *  required to do this unless you know your stream will use seek to
     *  move backwards such as when backtracking.
     *
     *  This is different from rewind in its multi-directional
     *  requirement and in that its argument is strictly an input cursor (index).
     *
     *  For char streams, seeking forward must update the stream state such
     *  as line number.  For seeking backwards, you will be presumably
     *  backtracking using the mark/rewind mechanism that restores state and
     *  so this method does not need to update state when seeking backwards.
     *
     *  Currently, this method is only used for efficient backtracking, but
     *  in the future it may be used for incremental parsing.
     */
    virtual void	seek(ANTLR_MARKER index) = 0;

};

ANTLR_END_NAMESPACE()

#endif