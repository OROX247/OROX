# Lessons learned (append, newest at the bottom)
- three.js r128 has no userData on textures. Track shared textures in a Set.
- Many point lights make shader compiles freeze the page. Use emissive materials plus glow sprites instead.
- Live AI video cannot give solid ground: it repaints every frame and the world swims. Use real textures on real geometry.
- Newer Decart models report fps as an object ({ideal, max}); read the number before calling captureStream.
- The published claude.ai link blocks outside services. Anything that calls Decart or Poly Haven must run from the local file.
