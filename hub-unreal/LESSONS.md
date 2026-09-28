# Lessons learned (append, newest at the bottom)
- The C++ scaffold was written without a compiler at hand. Expect a handful of compile errors on the first build (header names, Enhanced Input API details); fix them in place rather than restructuring.
- Enhanced Input assets are created at runtime in AHubCharacter::EnsureInputAssets so the game plays before any input assets exist in Content. Once BP_HubCharacter has real IA_/IMC_ assets assigned, the runtime set is skipped.
- Every trigger (portal, coin, pad) uses the HubInteract collision profile from DefaultEngine.ini: overlaps pawns only.
