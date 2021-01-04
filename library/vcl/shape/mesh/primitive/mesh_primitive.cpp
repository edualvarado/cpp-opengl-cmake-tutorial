#include "mesh_primitive.hpp"
#include "vcl/math/math.hpp"

namespace vcl
{

	static buffer<uint3> connectivity_grid(size_t Nu, size_t Nv)
	{
		buffer<uint3> connectivity;
		for(size_t ku=0; ku<Nu-1; ++ku) {
			for(size_t kv=0; kv<Nv-1; ++kv) {
				unsigned int k00 = static_cast<unsigned int>(kv   + Nv* ku);
				unsigned int k10 = static_cast<unsigned int>(kv+1 + Nv* ku);
				unsigned int k01 = static_cast<unsigned int>(kv   + Nv*(ku+1));
				unsigned int k11 = static_cast<unsigned int>(kv+1 + Nv*(ku+1));

				connectivity.push_back(uint3{k00, k10, k11});
				connectivity.push_back(uint3{k00, k11, k01});
			}
		}
		return connectivity;
	}

	mesh mesh_primitive_cylinder(float radius, vec3 const& p0, vec3 const& p1, int Nu, int Nv, bool is_closed)
	{
		vec3 const p01 = p1-p0;
		float const L = norm(p01);
		assert_vcl(L>1e-6f, "Cylinder has 0 length");

		vec3 const dir = p01/L;
		rotation const R = rotation_between_vector({0,0,1}, dir);

		mesh shape;
		for( size_t ku=0; ku<size_t(Nu); ++ku ) {
			for( size_t kv=0; kv<size_t(Nv); ++kv ) {
				float const u = ku/(Nu-1.0f);
				float const v = kv/(Nv-1.0f);

				float const theta = 2 * pi * v;

				// cylinder oriented along local z-axis
				vec3 const q = {radius*std::cos(theta), radius*std::sin(theta), L*u};

				// rotate and translate to p1
				vec3 const p = R*q + p0;

				// normal
				vec3 const n = R * vec3{std::cos(theta), std::sin(theta), 0};
				// uv
				vec2 const uv = {u,v};

				shape.position.push_back(p);
				shape.normal.push_back(n);
				shape.uv.push_back(uv);
			}
		}

		shape.connectivity = connectivity_grid(Nu,Nv);

		if(is_closed){
			shape.push_back( mesh_primitive_disc(radius, p0, dir, Nv).flip_connectivity() );
			shape.push_back( mesh_primitive_disc(radius, p1, dir, Nv) );
		}

		shape.fill_empty_field();
		
		return shape;
	}

	mesh mesh_primitive_triangle(vec3 const& p0, vec3 const& p1, vec3 const& p2)
	{
		vec3 const n = normalize(cross(normalize(p1-p0), normalize(p2-p0)));

		mesh shape;
		shape.position = {p0, p1, p2};
		shape.normal = {n,n,n};
		shape.uv = {vec2{0,0}, vec2{0,1}, vec2{1,0}};
		shape.connectivity = {{0,1,2}};
		shape.fill_empty_field();
		return shape;
	}
	mesh mesh_primitive_quadrangle(vec3 const& p00, vec3 const& p10, vec3 const& p11, vec3 const& p01)
	{
		mesh shape;
		shape.position = {p00, p10, p11, p01};
		shape.uv = {vec2{0,0}, vec2{1,0}, vec2{1,1}, vec2{0,1}};

		shape.normal = {
			normalize(cross(normalize(p10-p00), normalize(p01-p00))),
			normalize(cross(normalize(p11-p10), normalize(p00-p10))),
			normalize(cross(normalize(p01-p11), normalize(p10-p11))), 
			normalize(cross(normalize(p00-p01), normalize(p11-p01)))};

		shape.connectivity = {{0,1,2}, {0,2,3}};
		shape.fill_empty_field();
		return shape;
	}

	mesh mesh_primitive_disc(float radius, vec3 const& center, vec3 const& normal, int N)
	{
		assert_vcl(radius>0, "Disc radius ("+str(radius)+") must be >0");
		assert_vcl(N>2, "Disc samples ("+str(N)+") must be >2");

		mesh shape;

		rotation const r = rotation_between_vector({0,0,1}, normal);

		for (size_t k = 0; k < size_t(N); ++k)
		{
			float const u = k/(N-1.0f);
			vec3 const p = radius * r * vec3(std::cos(2*pi*u), std::sin(2*pi*u), 0.0f) + center;
			shape.position.push_back(p);
			shape.uv.push_back({float(std::cos(2*pi*u))*0.5f+0.5f, float(std::sin(2*pi*u))*0.5f+0.5f});
			shape.normal.push_back(normal);
		}
		// middle point
		shape.position.push_back(center);
		shape.uv.push_back({0.5f, 0.5f});
		shape.normal.push_back(normal);

		for (size_t k = 0; k < size_t(N-1); ++k)
			shape.connectivity.push_back( uint3{ unsigned(N), unsigned(k), unsigned(k+1)});

		shape.fill_empty_field();
		return shape;
	}

	mesh mesh_primitive_sphere(float radius, vec3 const& center, int Nu, int Nv)
	{
		assert_vcl(radius>0, "Sphere radius should be > 0");
		assert_vcl(Nu>2 && Nv>2, "Sphere samples should be > 2");

		mesh shape;
		for( size_t ku=0; ku<size_t(Nu); ++ku ) {
			for( size_t kv=0; kv<size_t(Nv); ++kv ) {
				float const u = ku/(Nu-1.0f);
				float const alpha = kv/(Nv-1.0f);
				float const v = 1.0f/(Nv+1.0f) * (1-alpha) + alpha* Nv/(Nv+1.0f) ;

				float const theta = 2.0f * pi * (u-0.5f);
				float const phi   =        pi * (v-0.5f);

				// spherical coordinates
				vec3 const n = {
					std::cos(phi)*std::cos(theta), 
					std::cos(phi)*std::sin(theta), 
					std::sin(phi)};
				vec3 const p = radius * n + center;
				vec2 const uv = {u,v};

				shape.position.push_back(p);
				shape.normal.push_back(n);
				shape.uv.push_back(uv);
			}
		}

		shape.connectivity = connectivity_grid(Nu,Nv);

		
		// poles
		for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
		{
			shape.position.push_back(center+radius*vec3{0,0,-1.0f});
			shape.normal.push_back(vec3{0,0,-1.0f});
			shape.uv.push_back({ku/(Nu-1.0f),0.0f});
		}
		for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
			shape.connectivity.push_back({Nu*Nv+ku, Nv*ku, Nv*(ku+1)});

		for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
		{
			shape.position.push_back(center+radius*vec3{0,0,1.0f});
			shape.normal.push_back(vec3{0,0,1.0f});
			shape.uv.push_back({ku/(Nu-1.0f),1.0f});
		}
		for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
			shape.connectivity.push_back({Nu*Nv+Nu-1+ku, Nv-1+Nv*(ku+1), Nv-1+Nv*ku});

		

		shape.fill_empty_field();
		shape.flip_connectivity();
		return shape;
	}



	mesh mesh_primitive_grid(vec3 const& p00, vec3 const& p10, vec3 const& p11, vec3 const& p01, int Nu, int Nv)
	{
		assert_vcl(Nu>1, "Grid sample must be >1");
		assert_vcl(Nv>1, "Grid sample must be >1");

		mesh shape;
		for( size_t ku=0; ku<size_t(Nu); ++ku ) {
			for( size_t kv=0; kv<size_t(Nv); ++kv ) {

				float const u = ku/(Nu-1.0f);
				float const v = kv/(Nv-1.0f);

				vec3 const p = (1-u)*(1-v)*p00 + u*(1-v)*p10 + u*v*p11 + (1-u)*v*p01;

				vec3 const dpdu = (1-u)*(-p00+p01)+u*(-p10+p11);
				vec3 const dpdv = (1-v)*(-p00+p10)+v*( p11-p01);
				vec3 const n = normalize(cross( dpdv, dpdu));
				vec2 const uv = {u,v};

				shape.position.push_back(p);
				shape.normal.push_back(n);
				shape.uv.push_back(uv);
			}
		}
     	shape.connectivity = connectivity_grid(Nu,Nv);
		shape.fill_empty_field();
		shape.flip_connectivity();
		return shape;
	}
	
	mesh mesh_primitive_torus(float r_major, float r_minor, vec3 const& center, vec3 const& axis_orientation, int Nu, int Nv)
	{
		assert_vcl(r_major>0, "Torus radius must be >0");
		assert_vcl(r_minor>0, "Torus radius must be >0");
		assert_vcl(Nu>2, "Torus samples must be >2");
		assert_vcl(Nv>2, "Torus samples must be >2");

		rotation R = rotation_between_vector({0,0,1}, axis_orientation);

		mesh shape;
		for( size_t ku=0; ku<size_t(Nu); ++ku ) {
			for( size_t kv=0; kv<size_t(Nv); ++kv ) {

				float const u = ku/(Nu-1.0f);
				float const v = kv/(Nv-1.0f);

				float const theta = 2*pi*v;
				float const phi = 2*pi*u;

				vec3 const p = {
					(r_major + r_minor*std::cos(theta))*std::cos(phi),
					(r_major + r_minor*std::cos(theta))*std::sin(phi),
					r_minor*std::sin(theta)};
				vec3 const d_theta = {-std::sin(theta)*std::cos(phi), -std::sin(theta)*std::sin(phi), std::cos(theta)};
				vec3 const d_phi = {-(r_major+r_minor*std::cos(theta))*std::sin(phi), (r_major+r_minor*std::cos(theta))*std::cos(phi), 0.0f};
				vec3 const n = normalize(cross(d_phi, d_theta));


				shape.position.push_back(R*p+center);
				shape.normal.push_back(R*n);
				shape.uv.push_back({u,v});
			}
		}
		shape.connectivity = connectivity_grid(Nu,Nv);
		shape.fill_empty_field();
		return shape;
	}
	mesh mesh_primitive_cone(float radius, float height, vec3 const& center_of_base, vec3 const& axis_direction, bool is_closed_base, int Nu, int Nv)
	{
		assert_vcl(radius>0, "Cone radius must be >0");
		assert_vcl(height>0, "Cone height must be >0");
		assert_vcl(Nu>2, "Cone samples must be >2");
		assert_vcl(Nv>1, "Cone samples must be >1");


		mesh shape;
		rotation R = rotation_between_vector({0,0,1}, axis_direction);

		//base
		for (size_t ku = 0; ku < size_t(Nu); ++ku)
		{
			for (size_t kv = 0; kv < size_t(Nv); ++kv)
			{
				float const u = ku/(Nu-1.0f);
				float const v = kv/float(Nv) ;

				float const r = radius*(1-v);

				vec3 const p = R*vec3(r*std::cos(2*pi*u), r*std::sin(2*pi*u), height*v) + center_of_base;
				vec3 const n = R*normalize(vec3{std::cos(2*pi*u), std::sin(2*pi*u), radius/height });
				vec2 const uv = {(1-v)*std::cos(2*pi*u)*0.5f+0.5f, (1-v)*std::sin(2*pi*u)*0.5f+0.5f};

				shape.position.push_back(p);
				shape.normal.push_back(n);
				shape.uv.push_back(uv);
			}
		}

		shape.connectivity = connectivity_grid(Nu,Nv);
		shape.flip_connectivity();

		//Extremity
		for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
		{
			float const u = ku/(Nu-1.0f);
			vec3 const p = R*vec3{0,0,height}+center_of_base;
			vec3 const n = R*normalize(vec3{std::cos(2*pi*u), std::sin(2*pi*u), radius/height });
			vec2 const uv = {0.5f, 0.5f};

			shape.position.push_back(p);
			shape.normal.push_back(n);
			shape.uv.push_back(uv);
		}

		for (size_t ku = 0; ku < size_t(Nu-1); ++ku)
			shape.connectivity.push_back({Nv*ku+Nv-1, Nv*(ku+1)+Nv-1, Nu*Nv+ku});


		if(is_closed_base)
			shape.push_back( mesh_primitive_disc(radius, center_of_base, axis_direction, Nu).flip_connectivity() );

		shape.fill_empty_field();
		return shape;


	}

	mesh mesh_primitive_cube(vec3 const& center, float edge_length)
	{
		vec3 u = edge_length*vec3{1,1,1};
		vec3 p000 = center - u/2.0f;
		vec3 p100 = p000 + u*vec3{1,0,0};
		vec3 p110 = p000 + u*vec3{1,1,0};
		vec3 p010 = p000 + u*vec3{0,1,0};
		vec3 p001 = p000 + u*vec3{0,0,1};
		vec3 p101 = p000 + u*vec3{1,0,1};
		vec3 p111 = p000 + u*vec3{1,1,1};
		vec3 p011 = p000 + u*vec3{0,1,1};

		mesh shape;
		shape.push_back(mesh_primitive_quadrangle(p000, p100, p101, p001));
		shape.push_back(mesh_primitive_quadrangle(p100, p110, p111, p101));
		shape.push_back(mesh_primitive_quadrangle(p110, p010, p011, p111));
		shape.push_back(mesh_primitive_quadrangle(p010, p000, p001, p011));
		shape.push_back(mesh_primitive_quadrangle(p001, p101, p111, p011));
		shape.push_back(mesh_primitive_quadrangle(p100, p000, p010, p110));

		return shape;
	}

	//mesh mesh_primitive_cubic_grid(vec3 const& p000={0,0,0}, vec3 const& p100={1,0,0}, vec3 const& p110={1,1,0}, vec3 const& p010={0,1,0}, vec3 const& p001={0,0,1}, vec3 const& p101={1,0,1}, vec3 const& p111={1,1,1}, vec3 const& p011={0,1,1}, int Nx=10, int Ny=10, int Nz=10);
	mesh mesh_primitive_cubic_grid(vec3 const& p000, vec3 const& p100, vec3 const& p110, vec3 const& p010, vec3 const& p001, vec3 const& p101, vec3 const& p111, vec3 const& p011, int Nx, int Ny, int Nz)
	{
		assert_vcl(Nx>=2 && Ny>=2 && Nz>=2, "Nx, Ny, Nz must be > 2");

		//vec3 u = edge_length*vec3{1,1,1};
		//vec3 p000 = center - u/2.0f;
		//vec3 p100 = p000 + u*vec3{1,0,0};
		//vec3 p110 = p000 + u*vec3{1,1,0};
		//vec3 p010 = p000 + u*vec3{0,1,0};
		//vec3 p001 = p000 + u*vec3{0,0,1};
		//vec3 p101 = p000 + u*vec3{1,0,1};
		//vec3 p111 = p000 + u*vec3{1,1,1};
		//vec3 p011 = p000 + u*vec3{0,1,1};

		mesh shape;
		shape.push_back(mesh_primitive_grid(p000, p100, p101, p001, Nx, Nz));
		shape.push_back(mesh_primitive_grid(p100, p110, p111, p101, Ny, Nz));
		shape.push_back(mesh_primitive_grid(p110, p010, p011, p111, Nx, Nz));
		shape.push_back(mesh_primitive_grid(p010, p000, p001, p011, Ny, Nz));
		shape.push_back(mesh_primitive_grid(p001, p101, p111, p011, Nx, Ny));
		shape.push_back(mesh_primitive_grid(p100, p000, p010, p110, Nx, Ny));

		return shape;
	}

	mesh mesh_primitive_tetrahedron(vec3 const& p0, vec3 const& p1, vec3 const& p2, vec3 const& p3)
	{
		mesh shape;
		shape.push_back(mesh_primitive_triangle(p0,p2,p1));
		shape.push_back(mesh_primitive_triangle(p0,p1,p3));
		shape.push_back(mesh_primitive_triangle(p1,p2,p3));
		shape.push_back(mesh_primitive_triangle(p2,p0,p3));
		return shape;
	}

	//mesh mesh_primitive_cube_grid(vec3 const& center, float edge_length, int Nx, int Ny, int Nz)
	//{

	//}

	mesh mesh_primitive_arrow(vec3 const& p0, vec3 const& p1, float cylinder_radius, float cone_length_scale, float cone_radius_scale, int N)
	{
		assert_vcl(N>2, "Arrow sample must be >2");

		float const cone_radius = cone_radius_scale * cylinder_radius;
		float const cone_length = cone_length_scale * cylinder_radius;

		assert_vcl(cone_length<norm(p1-p0), "Too short arrow - length of cone > length of array");
		vec3 const u = normalize(p1-p0);
		vec3 const p_extremity = p1-u*cone_length;

		mesh const cone_extremity = mesh_primitive_cone(cone_radius, cone_length, p_extremity, u, true, N);
		mesh const cylinder = mesh_primitive_cylinder(cylinder_radius, p0, p_extremity, 2, N, false);

		mesh shape;
		shape.push_back(cone_extremity);
		shape.push_back(cylinder);

		shape.fill_empty_field();
		return shape;
	}

	mesh mesh_primitive_frame(frame const& f, float scale, vec3 const& color_ux, vec3 const& color_uy, vec3 const& color_uz, vec3 const& color_sphere, float frame_thickness)
	{
		vec3 const& p0 = f.position;
		vec3 const p1 = p0 + scale * f.ux();
		vec3 const p2 = p0 + scale * f.uy();
		vec3 const p3 = p0 + scale * f.uz();

		mesh ux = mesh_primitive_arrow(p0,p1,frame_thickness*scale);
		mesh uy = mesh_primitive_arrow(p0,p2,frame_thickness*scale);
		mesh uz = mesh_primitive_arrow(p0,p3,frame_thickness*scale);
		ux.color.fill(color_ux);
		uy.color.fill(color_uy);
		uz.color.fill(color_uz);

		mesh sphere = mesh_primitive_sphere(2.5*frame_thickness*scale, p0, 40,20);
		sphere.color.fill(color_sphere);

		mesh shape;
		shape.push_back(ux).push_back(uy).push_back(uz).push_back(sphere);
		return shape;
	}
	
}