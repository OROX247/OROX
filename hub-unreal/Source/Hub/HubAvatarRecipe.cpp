#include "HubAvatarRecipe.h"

namespace
{
	struct FColourWord { const TCHAR* Word; FLinearColor Colour; };
	static FLinearColor Hex(uint32 H) { return FLinearColor::FromSRGBColor(FColor((H >> 16) & 255, (H >> 8) & 255, H & 255)); }

	static const TMap<FString, uint32>& ColourWords()
	{
		static TMap<FString, uint32> M = {
			{TEXT("red"),0xc0392b},{TEXT("crimson"),0xb3172a},{TEXT("scarlet"),0xd62828},{TEXT("orange"),0xe8772e},{TEXT("amber"),0xf2a900},{TEXT("gold"),0xd4a93a},{TEXT("golden"),0xd4a93a},
			{TEXT("yellow"),0xf2d43f},{TEXT("lime"),0x9dff6a},{TEXT("green"),0x2f9e44},{TEXT("emerald"),0x1f8a5a},{TEXT("teal"),0x1d7a78},{TEXT("turquoise"),0x2dc7c0},{TEXT("cyan"),0x5ce1e6},
			{TEXT("aqua"),0x4dd8e0},{TEXT("blue"),0x2b6cd6},{TEXT("navy"),0x1f2a44},{TEXT("indigo"),0x3f3ba8},{TEXT("violet"),0x7d4fd6},{TEXT("purple"),0x6a3fb0},{TEXT("magenta"),0xd13cc1},
			{TEXT("pink"),0xff4fa3},{TEXT("rose"),0xe86aa0},{TEXT("white"),0xeceef2},{TEXT("ivory"),0xf2efe8},{TEXT("cream"),0xf0e6c8},{TEXT("silver"),0xb9bec8},{TEXT("grey"),0x7d8189},
			{TEXT("gray"),0x7d8189},{TEXT("charcoal"),0x2a2a30},{TEXT("black"),0x17171d},{TEXT("brown"),0x5a3d28},{TEXT("tan"),0xc8a878},{TEXT("beige"),0xd8c8a8},{TEXT("bronze"),0xa56a2c},
			{TEXT("copper"),0xb8622a},{TEXT("rust"),0xa44a1e},{TEXT("olive"),0x6f6a3a},{TEXT("mint"),0x8fd3a8},{TEXT("lavender"),0xb18cff},{TEXT("peach"),0xf5b58f},{TEXT("coral"),0xff7f66},
			{TEXT("maroon"),0x6b1d2e},{TEXT("burgundy"),0x6b1d2e},{TEXT("chrome"),0xd0d4dc},{TEXT("steel"),0x8f97a3},{TEXT("bone"),0xe6dfd0},{TEXT("sand"),0xd9b27c},{TEXT("neon"),0x5ce1e6}
		};
		return M;
	}

	struct FSpecies { EHubBody Body; EHubHead Head; EHubMaterial Mat; TArray<FName> Feats; uint32 Main; uint32 Second; EHubEyes Eyes; float Height; EHubBuild Build; };
	static const TMap<FString, FSpecies>& Species()
	{
		static TMap<FString, FSpecies> M = {
			{TEXT("robot"),   {EHubBody::Robot, EHubHead::Screen, EHubMaterial::Plate, {TEXT("antenna")}, 0x8f97a3, 0x2a2a30, EHubEyes::Dots, 1.8f, EHubBuild::Normal}},
			{TEXT("android"), {EHubBody::Robot, EHubHead::Visor, EHubMaterial::Chrome, {}, 0xb9bec8, 0x2a2a30, EHubEyes::Visor, 1.8f, EHubBuild::Normal}},
			{TEXT("knight"),  {EHubBody::Humanoid, EHubHead::Helmet, EHubMaterial::Plate, {TEXT("sword"), TEXT("cape")}, 0xb9bec8, 0x2a2a30, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("samurai"), {EHubBody::Humanoid, EHubHead::Helmet, EHubMaterial::Plate, {TEXT("sword"), TEXT("horns")}, 0x6b1d2e, 0xd4a93a, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("astronaut"),{EHubBody::Humanoid, EHubHead::Visor, EHubMaterial::Plate, {TEXT("backpack")}, 0xeceef2, 0xb9bec8, EHubEyes::Visor, 1.8f, EHubBuild::Normal}},
			{TEXT("ninja"),   {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("mask")}, 0x17171d, 0x2a2a30, EHubEyes::Slits, 1.8f, EHubBuild::Slim}},
			{TEXT("wizard"),  {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("hood"), TEXT("staff")}, 0x3b2a5a, 0x6a3fb0, EHubEyes::Dots, 1.8f, EHubBuild::Normal}},
			{TEXT("king"),    {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("crown"), TEXT("cape")}, 0x6b1d2e, 0xd4a93a, EHubEyes::Dots, 1.8f, EHubBuild::Normal}},
			{TEXT("angel"),   {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("wings"), TEXT("halo")}, 0xf2efe8, 0xeceef2, EHubEyes::Dots, 1.8f, EHubBuild::Normal}},
			{TEXT("demon"),   {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Matte, {TEXT("horns"), TEXT("tail"), TEXT("wings")}, 0x7a1a1a, 0x2a2a30, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("skeleton"),{EHubBody::Humanoid, EHubHead::Skull, EHubMaterial::Stone, {}, 0xe6dfd0, 0xc8c0b0, EHubEyes::Dots, 1.8f, EHubBuild::Slim}},
			{TEXT("alien"),   {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Jelly, {TEXT("antenna")}, 0x6fbf5a, 0x2f9e44, EHubEyes::Wide, 1.8f, EHubBuild::Slim}},
			{TEXT("ghost"),   {EHubBody::Blob, EHubHead::Bare, EHubMaterial::Jelly, {}, 0xeceef2, 0xeceef2, EHubEyes::Dots, 1.8f, EHubBuild::Normal}},
			{TEXT("blob"),    {EHubBody::Blob, EHubHead::Bare, EHubMaterial::Jelly, {}, 0x9dff6a, 0x2f9e44, EHubEyes::One, 1.8f, EHubBuild::Normal}},
			{TEXT("fox"),     {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("snout"), TEXT("tail")}, 0xe8772e, 0xf2efe8, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("wolf"),    {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("snout"), TEXT("tail")}, 0x7d8189, 0xdcdde0, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("cat"),     {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("tail")}, 0x2a2a30, 0xdcdde0, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("dog"),     {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("snout"), TEXT("tail")}, 0x8a5a2a, 0xd8c8a8, EHubEyes::Wide, 1.8f, EHubBuild::Normal}},
			{TEXT("tiger"),   {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("snout"), TEXT("tail")}, 0xe8772e, 0x17171d, EHubEyes::Slits, 1.8f, EHubBuild::Heavy}},
			{TEXT("bear"),    {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("snout")}, 0x5a3d28, 0x8a5a2a, EHubEyes::Dots, 1.8f, EHubBuild::Huge}},
			{TEXT("rabbit"),  {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("ears"), TEXT("tail")}, 0xdcdde0, 0xf5b58f, EHubEyes::Wide, 1.3f, EHubBuild::Normal}},
			{TEXT("dragon"),  {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Plate, {TEXT("horns"), TEXT("wings"), TEXT("tail"), TEXT("spikes"), TEXT("snout")}, 0x1f8a5a, 0xd4a93a, EHubEyes::Slits, 2.2f, EHubBuild::Heavy}},
			{TEXT("lizard"),  {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Plate, {TEXT("tail"), TEXT("snout")}, 0x2f9e44, 0x9dff6a, EHubEyes::Slits, 1.8f, EHubBuild::Normal}},
			{TEXT("bird"),    {EHubBody::Beast, EHubHead::Animal, EHubMaterial::Fur, {TEXT("wings"), TEXT("tail")}, 0x2b6cd6, 0xffd166, EHubEyes::Wide, 1.4f, EHubBuild::Normal}},
			{TEXT("golem"),   {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Stone, {}, 0x7a7570, 0x5a5f6b, EHubEyes::Dots, 2.3f, EHubBuild::Huge}},
			{TEXT("pirate"),  {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("sword"), TEXT("cape")}, 0x2a2a30, 0xc0392b, EHubEyes::Dots, 1.8f, EHubBuild::Normal}},
			{TEXT("soldier"), {EHubBody::Humanoid, EHubHead::Helmet, EHubMaterial::Matte, {TEXT("backpack")}, 0x4a5a3a, 0x2a2a30, EHubEyes::Visor, 1.8f, EHubBuild::Normal}},
			{TEXT("vampire"), {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("cape")}, 0x17171d, 0x6b1d2e, EHubEyes::Slits, 1.8f, EHubBuild::Slim}},
			{TEXT("elf"),     {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Cloth, {TEXT("ears"), TEXT("hood")}, 0x2f6a3a, 0xc8a878, EHubEyes::Dots, 1.8f, EHubBuild::Slim}},
			{TEXT("dwarf"),   {EHubBody::Humanoid, EHubHead::Helmet, EHubMaterial::Plate, {}, 0x8a5a2a, 0x8f97a3, EHubEyes::Dots, 1.3f, EHubBuild::Heavy}},
			{TEXT("fairy"),   {EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Glass, {TEXT("wings")}, 0xb18cff, 0x8fd3a8, EHubEyes::Wide, 1.2f, EHubBuild::Slim}},
			{TEXT("superhero"),{EHubBody::Humanoid, EHubHead::Bare, EHubMaterial::Neon, {TEXT("cape"), TEXT("mask")}, 0x2b6cd6, 0xc0392b, EHubEyes::Visor, 1.8f, EHubBuild::Normal}}
		};
		return M;
	}
	static const TMap<FString, FString>& Aliases()
	{
		static TMap<FString, FString> M = { {TEXT("droid"),TEXT("robot")},{TEXT("mech"),TEXT("robot")},{TEXT("bot"),TEXT("robot")},{TEXT("cyborg"),TEXT("android")},{TEXT("paladin"),TEXT("knight")},{TEXT("warrior"),TEXT("knight")},
			{TEXT("spaceman"),TEXT("astronaut")},{TEXT("assassin"),TEXT("ninja")},{TEXT("mage"),TEXT("wizard")},{TEXT("witch"),TEXT("wizard")},{TEXT("sorcerer"),TEXT("wizard")},{TEXT("queen"),TEXT("king")},{TEXT("prince"),TEXT("king")},{TEXT("princess"),TEXT("king")},
			{TEXT("devil"),TEXT("demon")},{TEXT("skull"),TEXT("skeleton")},{TEXT("spirit"),TEXT("ghost")},{TEXT("phantom"),TEXT("ghost")},{TEXT("slime"),TEXT("blob")},{TEXT("jelly"),TEXT("blob")},{TEXT("werewolf"),TEXT("wolf")},{TEXT("kitten"),TEXT("cat")},
			{TEXT("puppy"),TEXT("dog")},{TEXT("bunny"),TEXT("rabbit")},{TEXT("drake"),TEXT("dragon")},{TEXT("gecko"),TEXT("lizard")},{TEXT("eagle"),TEXT("bird")},{TEXT("parrot"),TEXT("bird")},{TEXT("troll"),TEXT("golem")},{TEXT("hero"),TEXT("superhero")},{TEXT("trooper"),TEXT("soldier")} };
		return M;
	}
	static const TMap<FString, FName>& FeatureWords()
	{
		static TMap<FString, FName> M = { {TEXT("ears"),TEXT("ears")},{TEXT("ear"),TEXT("ears")},{TEXT("snout"),TEXT("snout")},{TEXT("horns"),TEXT("horns")},{TEXT("horn"),TEXT("horns")},{TEXT("horned"),TEXT("horns")},{TEXT("antlers"),TEXT("horns")},
			{TEXT("tail"),TEXT("tail")},{TEXT("wings"),TEXT("wings")},{TEXT("wing"),TEXT("wings")},{TEXT("winged"),TEXT("wings")},{TEXT("cape"),TEXT("cape")},{TEXT("cloak"),TEXT("cape")},{TEXT("hood"),TEXT("hood")},{TEXT("hooded"),TEXT("hood")},{TEXT("hoodie"),TEXT("hood")},
			{TEXT("backpack"),TEXT("backpack")},{TEXT("jetpack"),TEXT("jetpack")},{TEXT("sword"),TEXT("sword")},{TEXT("blade"),TEXT("sword")},{TEXT("katana"),TEXT("sword")},{TEXT("staff"),TEXT("staff")},{TEXT("wand"),TEXT("staff")},
			{TEXT("antenna"),TEXT("antenna")},{TEXT("antennae"),TEXT("antenna")},{TEXT("halo"),TEXT("halo")},{TEXT("crown"),TEXT("crown")},{TEXT("mask"),TEXT("mask")},{TEXT("masked"),TEXT("mask")},{TEXT("spikes"),TEXT("spikes")},{TEXT("spiky"),TEXT("spikes")},{TEXT("mohawk"),TEXT("spikes")} };
		return M;
	}
	static const TMap<FString, EHubMaterial>& MaterialWords()
	{
		static TMap<FString, EHubMaterial> M = { {TEXT("chrome"),EHubMaterial::Chrome},{TEXT("metal"),EHubMaterial::Chrome},{TEXT("metallic"),EHubMaterial::Chrome},{TEXT("steel"),EHubMaterial::Chrome},{TEXT("mirror"),EHubMaterial::Chrome},
			{TEXT("glass"),EHubMaterial::Glass},{TEXT("crystal"),EHubMaterial::Glass},{TEXT("ice"),EHubMaterial::Glass},{TEXT("fur"),EHubMaterial::Fur},{TEXT("furry"),EHubMaterial::Fur},{TEXT("fluffy"),EHubMaterial::Fur},
			{TEXT("cloth"),EHubMaterial::Cloth},{TEXT("fabric"),EHubMaterial::Cloth},{TEXT("stone"),EHubMaterial::Stone},{TEXT("rock"),EHubMaterial::Stone},{TEXT("marble"),EHubMaterial::Stone},{TEXT("neon"),EHubMaterial::Neon},{TEXT("luminous"),EHubMaterial::Neon},
			{TEXT("slime"),EHubMaterial::Jelly},{TEXT("gel"),EHubMaterial::Jelly},{TEXT("matte"),EHubMaterial::Matte},{TEXT("rubber"),EHubMaterial::Matte},{TEXT("leather"),EHubMaterial::Matte},{TEXT("armour"),EHubMaterial::Plate},{TEXT("armor"),EHubMaterial::Plate},{TEXT("plate"),EHubMaterial::Plate} };
		return M;
	}
	static const TMap<FString, FName>& PatternWords()
	{
		static TMap<FString, FName> M = { {TEXT("stripes"),TEXT("stripes")},{TEXT("striped"),TEXT("stripes")},{TEXT("plates"),TEXT("plates")},{TEXT("scales"),TEXT("plates")},{TEXT("circuits"),TEXT("circuits")},{TEXT("circuit"),TEXT("circuits")},{TEXT("digital"),TEXT("circuits")},
			{TEXT("checks"),TEXT("checks")},{TEXT("chequered"),TEXT("checks")},{TEXT("checkered"),TEXT("checks")},{TEXT("camo"),TEXT("camo")},{TEXT("camouflage"),TEXT("camo")} };
		return M;
	}
	static bool IsEyeWord(const FString& W) { return W == TEXT("eye") || W == TEXT("eyes"); }
}

FHubAvatarRecipe UHubAvatarLibrary::ParseDescription(const FString& Text)
{
	FHubAvatarRecipe R; R.Description = Text;
	FString Lower = Text.ToLower();
	for (TCHAR& C : Lower) if (!FChar::IsAlnum(C) && C != TEXT('\'')) C = TEXT(' ');
	TArray<FString> Words; Lower.ParseIntoArrayWS(Words);
	auto Stem = [](const FString& W) { if (W.EndsWith(TEXT("ies"))) return W.LeftChop(3) + TEXT("y"); if (W.EndsWith(TEXT("es"))) return W.LeftChop(2); if (W.EndsWith(TEXT("s"))) return W.LeftChop(1); return W; };

	// 1. species set the base look
	int32 SpeciesHits = 0;
	for (const FString& W : Words)
	{
		FString Key = W; if (const FString* A = Aliases().Find(Key)) Key = *A;
		if (!Species().Contains(Key)) { Key = Stem(W); if (const FString* A = Aliases().Find(Key)) Key = *A; }
		if (const FSpecies* S = Species().Find(Key))
		{
			R.Body = S->Body; R.Head = S->Head; R.Material = S->Mat; for (const FName& F : S->Feats) R.AddFeature(F);
			R.MainColour = Hex(S->Main); R.SecondColour = Hex(S->Second); R.Eyes = S->Eyes; R.Height = S->Height; R.Build = S->Build; SpeciesHits++;
		}
	}
	// 2. colours, with roles ("glowing blue eyes", "red cape", "gold trim")
	TArray<FLinearColor> General; bool bEyesSet = false;
	for (int32 i = 0; i < Words.Num(); i++)
	{
		const uint32* Hx = ColourWords().Find(Words[i]); if (!Hx) continue;
		FLinearColor Col = Hex(*Hx);
		if (i > 0 && (Words[i - 1] == TEXT("dark") || Words[i - 1] == TEXT("deep"))) Col *= 0.55f;
		if (i > 0 && (Words[i - 1] == TEXT("light") || Words[i - 1] == TEXT("pale"))) Col = FMath::Lerp(Col, FLinearColor::White, 0.4f);
		const FString Next = i + 1 < Words.Num() ? Words[i + 1] : TEXT(""), Next2 = i + 2 < Words.Num() ? Words[i + 2] : TEXT(""), Prev = i > 0 ? Words[i - 1] : TEXT("");
		if (IsEyeWord(Next) || IsEyeWord(Next2) || Prev == TEXT("glowing") || Next == TEXT("glow") || Next == TEXT("trim") || Next == TEXT("lights") || Next == TEXT("visor"))
		{
			if (IsEyeWord(Next) || IsEyeWord(Next2) || Prev == TEXT("glowing")) { R.EyeGlow = Col; bEyesSet = true; }
			R.GlowColour = Col; R.TrimColour = Col; continue;
		}
		static const TSet<FString> SecondWords = { TEXT("cape"), TEXT("cloak"), TEXT("hood"), TEXT("hoodie"), TEXT("scarf"), TEXT("robe"), TEXT("belt"), TEXT("boots"), TEXT("gloves"), TEXT("crown"), TEXT("wings"), TEXT("tail"), TEXT("mane"), TEXT("belly"), TEXT("chest"), TEXT("accents"), TEXT("and") };
		if (SecondWords.Contains(Next) && General.Num() > 0) { R.SecondColour = Col; continue; }
		General.Add(Col);
	}
	if (General.Num() > 0) { R.MainColour = General[0]; if (General.Num() > 1) R.SecondColour = General[1]; if (General.Num() > 2) { R.TrimColour = General[2]; if (!bEyesSet) R.GlowColour = General[2]; } }
	// 3. explicit words override the presets
	for (int32 i = 0; i < Words.Num(); i++)
	{
		const FString& W = Words[i]; const FString S = Stem(W); const FString Next = i + 1 < Words.Num() ? Words[i + 1] : TEXT(""); const FString Prev = i > 0 ? Words[i - 1] : TEXT("");
		if (const FName* F = FeatureWords().Find(W)) { if (Prev == TEXT("no") || Prev == TEXT("without")) R.Features.Remove(*F); else R.AddFeature(*F); }
		else if (const FName* F2 = FeatureWords().Find(S)) { R.AddFeature(*F2); }
		if (const EHubMaterial* M = MaterialWords().Find(W)) { const bool bMetalColour = (W == TEXT("gold") || W == TEXT("silver")); if (!bMetalColour || SpeciesHits == 0) R.Material = *M; }
		if (const FName* P = PatternWords().Find(W)) R.Pattern = *P;
		static const TSet<FString> Clothing = { TEXT("hoodie"), TEXT("robe"), TEXT("robes"), TEXT("suit"), TEXT("tracksuit"), TEXT("coat"), TEXT("jacket"), TEXT("dress"), TEXT("uniform"), TEXT("jumper"), TEXT("sweater"), TEXT("tuxedo") };
		if (Clothing.Contains(W) && (SpeciesHits == 0 || R.Body == EHubBody::Humanoid)) R.Material = EHubMaterial::Cloth;
		if (W == TEXT("helmet")) R.Head = EHubHead::Helmet; if (W == TEXT("visor")) R.Head = EHubHead::Visor; if (W == TEXT("skull")) R.Head = EHubHead::Skull; if (W == TEXT("screen") || W == TEXT("monitor")) R.Head = EHubHead::Screen;
		if (W == TEXT("tall") || W == TEXT("towering") || W == TEXT("lanky")) R.Height = FMath::Max(R.Height, 2.15f);
		if (W == TEXT("giant") || W == TEXT("huge") || W == TEXT("massive") || W == TEXT("enormous")) { R.Height = 2.4f; R.Build = EHubBuild::Huge; }
		if (W == TEXT("short") || W == TEXT("small") || W == TEXT("little") || W == TEXT("mini")) R.Height = FMath::Min(R.Height, 1.35f);
		if (W == TEXT("tiny") || W == TEXT("teeny")) R.Height = 0.9f;
		if (W == TEXT("slim") || W == TEXT("thin") || W == TEXT("skinny") || W == TEXT("slender") || W == TEXT("lean")) R.Build = EHubBuild::Slim;
		if (W == TEXT("muscular") || W == TEXT("buff") || W == TEXT("stocky") || W == TEXT("chunky") || W == TEXT("broad") || W == TEXT("bulky") || W == TEXT("heavy") || W == TEXT("fat") || W == TEXT("round")) R.Build = (R.Build == EHubBuild::Huge) ? EHubBuild::Huge : EHubBuild::Heavy;
		if (W == TEXT("cyclops") || (W == TEXT("one") && IsEyeWord(Next))) R.Eyes = EHubEyes::One;
		if ((W == TEXT("big") || W == TEXT("wide") || W == TEXT("huge") || W == TEXT("round") || W == TEXT("cute")) && IsEyeWord(Next)) R.Eyes = EHubEyes::Wide;
		if ((W == TEXT("narrow") || W == TEXT("slit") || W == TEXT("slits") || W == TEXT("angry") || W == TEXT("cat") || W == TEXT("snake")) && IsEyeWord(Next)) R.Eyes = EHubEyes::Slits;
		if ((W == TEXT("dot") || W == TEXT("dots") || W == TEXT("small") || W == TEXT("beady")) && IsEyeWord(Next)) R.Eyes = EHubEyes::Dots;
	}
	if (R.Body == EHubBody::Beast && R.Head == EHubHead::Visor) R.Head = EHubHead::Animal;
	R.Height = FMath::Clamp(R.Height, 0.6f, 2.4f);
	return R;
}

FString UHubAvatarLibrary::DescribeRecipe(const FHubAvatarRecipe& R)
{
	const TCHAR* Bodies[] = { TEXT("humanoid"), TEXT("robot"), TEXT("beast"), TEXT("blob") };
	const TCHAR* Builds[] = { TEXT("slim"), TEXT(""), TEXT("heavy"), TEXT("huge") };
	const TCHAR* Mats[] = { TEXT("cloth"), TEXT("matte"), TEXT("plate"), TEXT("chrome"), TEXT("glass"), TEXT("fur"), TEXT("jelly"), TEXT("stone"), TEXT("neon") };
	const TCHAR* Eyes[] = { TEXT("visor"), TEXT("dots"), TEXT("wide"), TEXT("slits"), TEXT("one") };
	TArray<FString> Bits;
	if (Builds[(int32)R.Build][0]) Bits.Add(Builds[(int32)R.Build]);
	if (R.Height >= 2.1f) Bits.Add(TEXT("tall")); else if (R.Height <= 1.3f) Bits.Add(TEXT("small"));
	Bits.Add(Mats[(int32)R.Material]); Bits.Add(Bodies[(int32)R.Body]);
	FString Out = FString::Join(Bits, TEXT(" "));
	if (R.Features.Num()) { TArray<FString> F; for (const FName& N : R.Features) F.Add(N.ToString()); Out += TEXT(", with ") + FString::Join(F, TEXT(", ")); }
	if (R.Pattern != TEXT("none")) Out += TEXT(", ") + R.Pattern.ToString();
	Out += FString::Printf(TEXT("; eyes: %s"), Eyes[(int32)R.Eyes]);
	return Out;
}

FString UHubAvatarLibrary::RandomLook(int32 Seed)
{
	static const TCHAR* Looks[] = { TEXT("a tall chrome knight with a red cape"), TEXT("a small fox in a green hoodie"), TEXT("a purple wizard with a golden staff"), TEXT("a chunky orange robot with antennae"), TEXT("a black cat with pink glowing eyes"),
		TEXT("a white angel with gold trim"), TEXT("a red demon with big horns"), TEXT("a grey wolf with a blue scarf"), TEXT("a tiny green alien"), TEXT("a pale ghost"), TEXT("a lime slime with one eye"), TEXT("a huge stone golem"), TEXT("a slim vampire in a black cape"),
		TEXT("a striped tiger in armour"), TEXT("a blue astronaut with a jetpack"), TEXT("a ninja in dark red"), TEXT("a golden dragon"), TEXT("a bear in a brown coat"), TEXT("a rabbit in a pink tracksuit"), TEXT("a skeleton pirate with a sword"),
		TEXT("a teal mermaid"), TEXT("a fairy with glowing yellow wings"), TEXT("a masked raccoon thief"), TEXT("a camo soldier with a backpack"), TEXT("a king in crimson and gold"), TEXT("a hooded elf archer"), TEXT("a stocky dwarf in steel armour"), TEXT("a cyborg in black chrome") };
	static const TCHAR* Extra[] = { TEXT(""), TEXT(""), TEXT(" with a cape"), TEXT(" with wings"), TEXT(" with spikes"), TEXT(" with a jetpack"), TEXT(" with glowing eyes"), TEXT(" with a crown"), TEXT(" in stripes"), TEXT(" tall"), TEXT(" small") };
	FRandomStream Rs(Seed);
	return FString(Looks[Rs.RandRange(0, UE_ARRAY_COUNT(Looks) - 1)]) + Extra[Rs.RandRange(0, UE_ARRAY_COUNT(Extra) - 1)];
}
