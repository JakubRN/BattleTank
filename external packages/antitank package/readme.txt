Hi everyone!

The model and textures are distributed under the following license:
https://creativecommons.org/licenses/by-nc/4.0/


How to use
-----------

1) Import the 3 fbx models (body, dome and barrel) as static meshes and all textures into Unreal Engine 4.

Setup the following socket positions:
	Dome 	Y: 0.0, Y: 0.0, Z: 308.0
	Barrel 	Y: 100.0, Y: 0.0, Z: 34.0
	Muzzle	Y: 410.0, Y: 0.0, Z: 0.0

2) Follow the "Material Setup" here:
	https://support.allegorithmic.com/documentation/display/SPDOC/Unreal+Engine+4

	In short:
		Normal maps (suffix _N):
			Compression Settings: Normalmap
  			Texture Group: WorldNormalMap
  			uncheck sRGB
		Ambient Occlusion, Roughness & Metallic (suffix _AORMT):
			uncheck sRGB

3) Create a Material for every static mesh. Add Texture Sample nodes for all 3 texture types (BC, N, AORMT).
 	Select the corresponding Texture in each node.
	Then connect the outputs to the corresponding inputs of the material:

	BC 		White pin 	-> Base Color
	N 		White pin	-> Normal
	AORMT	Red pin		-> Ambient Occlusion
			Green pin 	-> Roughness
			Blue pin	-> Metallic

	Switch the AORMT Texture Sample node Sampler Type to "Linear Color" and the N Texture Sampler Type to "Normal".

4) Add the materials in the static meshes' Material Slots.

5) Use in your AutoMortar BP. It's best to allow the Barrel a "Min Elevation Degrees" of -10.0 because of the higher
	elevation of the turrets' barrel. Otherwise the turret can only shoot you when you are pretty far away.


Hope you like the model and have fun with it. :)
If you redistribute it make sure to credit me.

It can also be found on Sketchfab:
https://sketchfab.com/models/212b2120338a4023a834d0c0081b406d

Michael Barth
