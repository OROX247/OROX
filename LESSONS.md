# Lessons learned (append, newest at the bottom)
- three.js r128 has no userData on textures. Track shared textures in a Set.
- Many point lights make shader compiles freeze the page. Use emissive materials plus glow sprites instead.
- Live AI video cannot give solid ground: it repaints every frame and the world swims. Use real textures on real geometry.
- Newer Decart models report fps as an object ({ideal, max}); read the number before calling captureStream.
- The published claude.ai link blocks outside services. Anything that calls Decart or Poly Haven must run from the local file.
- Testing: the game script is wrapped in an IIFE, so page.evaluate cannot see travel/state/p. Test an instrumented copy in the scratchpad (add `window.__ev = s => eval(s);` before the final `})();`); never edit index.html for tests.
- Testing: in headless Chromium with SwiftShader, scene.environment (the PMREM env map) turns every MeshStandardMaterial black, in every commit. Set scene.environment = null before test renders; this is a test-only workaround, not a game bug.
- Testing: SwiftShader runs at about 1-2 fps, so degrade() lowers quality mid-test and the frame loop can lag behind travel(). Set fSkip = 1e9 to freeze quality, and wait for frames before comparing screenshots, or the "same" view will look different.
- Procedural tiling textures: every sine/stripe must complete a whole number of cycles across the tile in both axes (e.g. phase (22x + 5y)/S), or a seam shows. Warp them only with an already-tileable field.
- A realm's fixed look breaks if anything in its build uses Math.random (rock tints did). Use rng(seed) for anything that is drawn.
- Testing hooks are built in now: `window.__hub` exposes state, p, cam, post, stats, scene, renderer, travel, buildWorld, startGame, degrade, freezeQuality() and gl (the renderer string). No instrumented copy needed. The game detects software GL (SwiftShader) itself and skips scene.environment, so headless screenshots are lit.
- Picture quality lives in one place: the post-processing section (`setupPost`): 4x MSAA -> half-res SSAO multiplied in -> bloom (threshold 0.92, glows only) -> gamma -> grade (vignette) -> SMAA. The composer renders in linear space, so the GammaCorrection pass is required; without it the picture is dark. Shadows render once per frame (`renderer.shadowMap.autoUpdate = false`, flagged in frame()), so any extra renderer.render call must not expect a fresh shadow map.
- Bloom on bright diffuse surfaces (sand, sky horizon) reads as haze. Keep the threshold above 0.9 so only emissive glows and the sun bloom.
- The quality ladder (`degrade`) drops effects first: SSAO, bloom, shadow resolution, grass, then pixel ratio to 1. It never disables shadows and never goes below pixel ratio 1.

