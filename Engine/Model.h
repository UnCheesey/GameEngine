#pragma once
#include "Mesh.h"

namespace nu {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<Mesh>& meshes) : m_meshes(meshes) {}

		void AddMeshes(const Mesh& mesh) { m_meshes.push_back(mesh); }

		void SetMeshes(const std::vector<Mesh>& meshes) { m_meshes = meshes; }
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

	private:
		std::vector<Mesh> m_meshes;
	};
}