WinMTR (Redux)
==============
**WinMTR (Redux)** in an extended fork of [Appnor's WinMTR](http://winmtr.net/) ([sourceforge](http://sourceforge.net/projects/winmtr/)) <br>
with IPv6 support and other different enhancements and bug fixes

### Download (binaries)
* [**view all available**](https://github.com/dragonzx/WinMTR/releases)

## Changelog
**Beta 1.01 - DragonZX**
- `[x]` - removed extra screens <br>
- `[x]` + added ARM version <br>
- `[x]` ! Code improvements <br>

**Release 1.00 - WhiteTiger**
- `[x]` - removed Windows 2000 support <br>
- `[x]` + added IPv6 support <br>
- `[x]` + clickable entries when stopped... *(why the heck wasn't it possible before?)* <br>
- `[x]` * added start delay of about 30ms for each hop *(870ms before the 30th hop gets queried) <br>
this should improve performance and reduces network load* <br>
- `[x]` ! fixed trace list freeze *(list didn't update while tracing, happens when tracing just one hop)* <br>
- `[x]` * theme support *(more fancy look :P)* <br>
- ~~`[ ]` + remembers window size~~ <br>
- `[ ]` ! CTRL+A works for host input <br>
- `[ ]` + host history: pressing del key or right mouse will remove selected entry <br>
- `[ ]` * new icon <br>

**Release 0.98 - [original Appnor](http://winmtr.net/) release** 
### Requirements
* Windows XP+
* Microsoft Visual C++ 2015-2022 Redistributables

### Fork history
There isn't that much to say actually, I've been using IPv6 for a few years now thanks to [**SixXS**](http://sixxs.net/)
and it always annoyed me that WinMTR couldn't handle IPv6... finally my ISP got some sort of IPv6 beta test.
And that's what I wanted to compare: native vs SixXS with long-term trace routes such as those WinMTR provides. <br>
Since there wasn't any WinMTR build with IPv6, I decided to do it myself ;) The result can be seen here :P <br>
*(after 1 day for IPv6, and 2 additional days to fix other stuff and polishing)*
