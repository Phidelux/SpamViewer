# SpamViewer

Simple Portable Any Map image Viewer is a basic viewer for the pnm file formats.

## Known issues & ToDos

- [ ] Maximum number of pixels is ignored in (plain) pixel maps (P3 and P6)
- [ ] Maximum color value is ignored in (plain) grayscale maps (P2 and P4)
- [ ] PGM and the PPM binary formats (P5 and P6) allow 16-bit color depths which is ot yet implemented
- [ ] Portable Arbitrary Map (PAM or P7) is not yet implemented
- [ ] If the first encoded block of a binary pnm equals a whitespace, it gets removed 
- [ ] Multiple images in one pnm file are ignored
- [ ] Doxyfile generated but no documentation yet
- [ ] The viewer does not support any transformations (translation, rotation or scaling)