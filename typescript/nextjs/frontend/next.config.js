/** @type {import('next').NextConfig} */
const nextConfig = {
  reactStrictMode: true,
  output: 'standalone',
  rewrites: async () => {
    const backendUrl = process.env.NODE_ENV === 'development' 
      ? 'http://backend:3001'
      : (process.env.API_URL || 'http://localhost:3001');
    
    return [
      {
        source: '/api/:path*',
        destination: `${backendUrl}/api/:path*`,
      },
    ];
  },
};

module.exports = nextConfig;